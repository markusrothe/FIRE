#include "GLVertexLayout.h"
#include <FIRE/glmfwd.h>
#include <cassert>
#include <glad/glad.h>

namespace FIRE
{
GLVertexLayout::GLVertexLayout(DrawMode drawMode)
    : VertexLayout(drawMode)
{

    glCreateBuffers(1, &m_vbo);
    glCreateVertexArrays(1, &m_vao);

    if(drawMode == DrawMode::INDEXED)
    {
        glCreateBuffers(1, &m_ibo);
        glVertexArrayElementBuffer(m_vao, m_ibo);
    }
}
GLVertexLayout::~GLVertexLayout()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);

    if(GetDrawMode() == DrawMode::INDEXED)
    {
        glDeleteBuffers(1, &m_ibo);
    }
}

void GLVertexLayout::BindLayout()
{
    assert(m_vao != 0);
    glBindVertexArray(m_vao);
}

void GLVertexLayout::ReleaseLayout()
{
    assert(m_vao != 0);
    glBindVertexArray(0);
}

void GLVertexLayout::BufferData(size_t size, void* data)
{
    glNamedBufferStorage(m_vbo, size, data, GL_DYNAMIC_STORAGE_BIT);
}

void GLVertexLayout::BufferIndexData(size_t size, void* data)
{
    glNamedBufferStorage(m_ibo, size, data, GL_DYNAMIC_STORAGE_BIT);
}

void GLVertexLayout::BufferSubData(size_t offset, size_t size, void* data)
{
    glNamedBufferSubData(m_vbo, offset, size, data);
}

void GLVertexLayout::AddVertexAttribute(uint32_t attribIndex, size_t size, size_t offset)
{
    auto bindingIndex = attribIndex;
    glEnableVertexArrayAttrib(m_vao, attribIndex);
    glVertexArrayVertexBuffer(m_vao, bindingIndex, m_vbo, offset, (GLsizei)(size * sizeof(float)));
    glVertexArrayAttribFormat(m_vao, attribIndex, static_cast<GLint>(size), GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(m_vao, attribIndex, bindingIndex);
}

} // namespace FIRE
