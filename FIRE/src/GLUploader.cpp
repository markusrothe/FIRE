#include "GLUploader.h"
#include "MaterialManager.h"
#include <FIRE/Renderable.h>

namespace FIRE
{
GLUploader::GLUploader(std::shared_ptr<MaterialManager> materialManager)
    : m_materialManager(std::move(materialManager))
{
}

std::tuple<GLuint, GLuint, GLuint>
GLUploader::Upload(Renderable const& renderable)
{
    auto it = m_uploadedRenderables.find(renderable.GetName());
    if(it != m_uploadedRenderables.end())
    {
        return it->second;
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    auto const verticesSize =
        renderable.GetMesh().Vertices().size() * sizeof(float) * 3;

    glBufferData(
        GL_ARRAY_BUFFER, verticesSize,
        &(renderable.GetMesh().VerticesAsArray())[0], GL_STATIC_DRAW);

    auto attribLocation = glGetAttribLocation(
        m_materialManager->GetShader(renderable.GetMaterial()), "vPos");
    glEnableVertexAttribArray(attribLocation);
    // GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei
    // stride, const void *pointer
    glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    GLuint ibo;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    auto const indicesSize =
        renderable.GetMesh().Indices().size() * sizeof(unsigned int);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indicesSize,
        &(renderable.GetMesh().Indices())[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    auto buffers = std::make_tuple(vao, vbo, ibo);
    m_uploadedRenderables.insert(std::make_pair(renderable.GetName(), buffers));
    return buffers;
}

} // namespace FIRE
