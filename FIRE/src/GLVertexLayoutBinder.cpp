#include "GLVertexLayoutBinder.h"
#include "VertexLayout.h"
#include <glad/glad.h>
namespace FIRE
{

void GLVertexLayoutBinder::Bind(VertexLayout const& vertexLayout)
{
    m_layout = vertexLayout;
    glBindVertexArray(m_layout.m_id);
}

void GLVertexLayoutBinder::BindVertexBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_layout.m_vertexBuffer);
}

void GLVertexLayoutBinder::BindIndexBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_layout.m_indexBuffer);
}

void GLVertexLayoutBinder::Release()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
} // namespace FIRE
