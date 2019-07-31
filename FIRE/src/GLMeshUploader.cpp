#include "GLMeshUploader.h"
#include "VertexLayout.h"
#include <FIRE/Mesh3D.h>
#include <glad/glad.h>
#define BUFFER_OFFSET(i) ((void*)(std::uintptr_t)(i))
namespace FIRE
{
namespace
{
void SpecifyVertexAttributes(VertexDeclaration const& vDecl, uint32_t shader)
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

GLuint UploadVertices(Mesh3D const& mesh, uint32_t shader)
{
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto const positions = mesh.Positions();
    auto const normals = mesh.Normals();
    auto const uvs = mesh.UVs();

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

    SpecifyVertexAttributes(mesh.GetVertexDeclaration(), shader);
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
VertexLayout GLMeshUploader::Upload(Mesh3D const& mesh, uint32_t shader)
{
    auto const it = m_uploadedMeshes.find(mesh.Name());
    if(it != m_uploadedMeshes.end())
    {
        return it->second;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint const vbo = UploadVertices(mesh, shader);
    GLuint const ibo = UploadIndices(mesh.Indices());

    VertexLayout layout(vao, vbo, ibo);
    m_uploadedMeshes.insert(std::make_pair(mesh.Name(), layout));
    return layout;
}
} // namespace FIRE
