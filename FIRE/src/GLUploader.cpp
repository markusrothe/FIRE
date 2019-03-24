#include "GLUploader.h"
#include "MaterialManager.h"
#include <FIRE/Mesh.h>
#include <FIRE/Renderable.h>
#include <FIRE/VertexDeclaration.h>
#include <iostream>
#define BUFFER_OFFSET(i) ((void*)(std::uintptr_t)(i))

namespace FIRE
{
namespace
{
void SpecifyVertexAttributes(VertexDeclaration const& vDecl, GLuint shader)
{
    for(auto const& vertexDeclSection : vDecl.GetSections())
    {
        auto attribLocation = glGetAttribLocation(
            shader,
            vertexDeclSection.first.c_str());

        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(
            attribLocation,
            vertexDeclSection.second.size,
            GL_FLOAT,
            GL_FALSE,
            vertexDeclSection.second.stride,
            BUFFER_OFFSET(vertexDeclSection.second.offset));
    }
}

GLuint UploadVertices(std::vector<float> const& vertices, VertexDeclaration const& vDecl, GLuint shader)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    auto const verticesSize = vertices.size() * sizeof(float);

    glBufferData(
        GL_ARRAY_BUFFER,
        verticesSize,
        &(vertices[0]),
        GL_STATIC_DRAW);
    SpecifyVertexAttributes(vDecl, shader);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

GLuint UploadIndices(std::vector<unsigned int> const& indices)
{
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    auto const indicesSize = indices.size() * sizeof(unsigned int);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indicesSize,
        &(indices[0]),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return ibo;
}

} // namespace

GLUploader::GLUploader(std::shared_ptr<MaterialManager> materialManager)
    : m_materialManager(std::move(materialManager))
{
}

std::tuple<GLuint, GLuint, GLuint>
GLUploader::Upload(Renderable const& renderable)
{
    auto const it = m_uploadedRenderables.find(renderable.GetName());
    if(it != m_uploadedRenderables.end())
    {
        return it->second;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Mesh const& mesh = renderable.GetMesh();

    GLuint const vbo = UploadVertices(
        mesh.VerticesAsArray(), mesh.GetVertexDeclaration(),
        m_materialManager->GetShader(renderable.GetMaterial()));

    GLuint const ibo = UploadIndices(mesh.Indices());

    auto buffers = std::make_tuple(vao, vbo, ibo);
    m_uploadedRenderables.insert(std::make_pair(renderable.GetName(), buffers));
    return buffers;
}

} // namespace FIRE
