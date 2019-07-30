#include "StaticGeometryRenderer.h"
#include <FIRE/Mesh3D.h>
#include <FIRE/MeshManager.h>
#include <FIRE/Renderable.h>
#include <iostream>
#include <stdexcept>
#define BUFFER_OFFSET(i) ((void*)(std::uintptr_t)(i))
namespace FIRE
{
namespace
{
void SetShaderUniforms(GLuint shader, std::map<std::string, std::pair<ShaderParameterType, std::any>> const& params)
{
    for(auto const& param : params)
    {
        auto const& name = param.first;
        auto const& paramType = param.second.first;
        auto const& paramVal = param.second.second;
        auto const uniformLocation = glGetUniformLocation(shader, name.c_str());

        switch(paramType)
        {
        case ShaderParameterType::MAT4x4:
        {
            auto const& uniformVal = std::any_cast<glm::mat4x4>(paramVal);
            glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(uniformVal));
            break;
        }
        case ShaderParameterType::VEC3:
        {
            auto const& uniformVal = std::any_cast<glm::vec3>(paramVal);
            glUniform3fv(uniformLocation, 1, glm::value_ptr(uniformVal));
            break;
        }
        }
    }
}

GLenum MapPrimitiveType(MeshPrimitives primitives)
{
    switch(primitives)
    {
    case MeshPrimitives::Points:
        return GL_POINTS;
    case MeshPrimitives::Lines:
        return GL_LINES;
    case MeshPrimitives::Triangles:
        return GL_TRIANGLES;
    default:
        assert(false);
        return GL_POINTS;
    }
}
void SpecifyVertexAttributes(VertexDeclaration const& vDecl, GLuint shader)
{
    for(auto const& vertexDeclSection : vDecl.GetSections())
    {
        auto attribLocation = glGetAttribLocation(
            shader,
            vertexDeclSection.first.c_str());

        auto const stride = 0u;
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(
            attribLocation,
            static_cast<GLint>(vertexDeclSection.second.size),
            GL_FLOAT,
            GL_FALSE,
            stride,
            BUFFER_OFFSET(vertexDeclSection.second.offset));
    }
}

void Write(std::vector<glm::vec3> const& data, size_t offset)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, data.size() * sizeof(data[0]), &data[0]);
}

void Write(std::vector<glm::vec2> const& data, size_t offset)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, data.size() * sizeof(data[0]), &data[0]);
}

GLuint UploadVertices(Mesh3D* mesh, GLuint shader)
{
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto const positions = mesh->Positions();
    auto const normals = mesh->Normals();
    auto const uvs = mesh->UVs();

    auto bufferSize = (positions.size() + normals.size()) * sizeof(glm::vec3) + uvs.size() * sizeof(glm::vec2);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);

    if(!positions.empty())
    {
        Write(positions, 0u);
    }

    if(!normals.empty())
    {
        Write(normals, positions.size() * sizeof(positions[0]));
    }

    if(!uvs.empty())
    {
        Write(uvs, positions.size() * sizeof(positions[0]) + normals.size() * sizeof(normals[0]));
    }

    SpecifyVertexAttributes(mesh->GetVertexDeclaration(), shader);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

GLuint UploadIndices(std::vector<unsigned int> const& indices)
{
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    auto const indicesSize = indices.size() * sizeof(unsigned int);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, &(indices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return ibo;
}
} // namespace
StaticGeometryRenderer::StaticGeometryRenderer(MeshManager& meshManager)
    : m_meshManager(meshManager)
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void StaticGeometryRenderer::Render(Renderable const& renderable)
{
    try
    {
        Draw(renderable, Upload(renderable));
    }
    catch(std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

GLVertexArrayObject StaticGeometryRenderer::Upload(Renderable const& renderable)
{
    auto const it = m_uploadedRenderables.find(renderable.name);
    if(it != m_uploadedRenderables.end())
    {
        return it->second;
    }

    Mesh3D* mesh = m_meshManager.Lookup(renderable.mesh);
    if(!mesh)
    {
        throw std::logic_error("Mesh not present");
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint const vbo = UploadVertices(mesh, renderable.material.ShaderId());
    GLuint const ibo = UploadIndices(mesh->Indices());

    GLVertexArrayObject arrObj(vao, vbo, ibo);
    m_uploadedRenderables.insert(std::make_pair(renderable.name, arrObj));
    return arrObj;
}

void StaticGeometryRenderer::Draw(Renderable const& renderable, GLVertexArrayObject vertexArrayObject)
{
    glBindVertexArray(vertexArrayObject.m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayObject.m_ibo);
    auto const shader = renderable.material.ShaderId();
    glUseProgram(shader);

    SetShaderUniforms(shader, renderable.material.GetShaderParameters());

    auto mesh = m_meshManager.Lookup(renderable.mesh);
    if(mesh)
    {
        glDrawElements(MapPrimitiveType(renderable.mesh.type.primitives), static_cast<GLsizei>(mesh->Indices().size()), GL_UNSIGNED_INT, 0);
    }

    glUseProgram(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

} // namespace FIRE
