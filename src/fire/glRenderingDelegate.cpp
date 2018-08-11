#include "glRenderingDelegate.h"
#include "renderable.h"
#include <algorithm>
#include <iostream>
#include <utility>

namespace Fire
{
void GLRenderingDelegate::Bind(Renderable* renderable)
{
    auto const alreadyUploadedIt = std::find_if(
        m_uploadedRenderables.begin(), m_uploadedRenderables.end(),
        [&renderable](
            std::unordered_map<Renderable*, BufferObjects>::value_type const&
                mapEntry) { return mapEntry.first == renderable; });

    if(alreadyUploadedIt == m_uploadedRenderables.end())
    {
        UploadRenderable(renderable);
    }

    glBindVertexArray(std::get<0>(m_uploadedRenderables[renderable]));
    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        std::get<2>(m_uploadedRenderables[renderable]));
}

void GLRenderingDelegate::Render(Renderable* renderable)
{
    auto uniformFunction = renderable->GetUniformFunction();
    if(uniformFunction)
    {
        uniformFunction();
    }

    glDrawElements(
        GL_TRIANGLES, renderable->GetIndexData().GetIndices().size(),
        GL_UNSIGNED_INT, 0);
}

void GLRenderingDelegate::Unbind(Renderable* renderable)
{
    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        std::get<2>(m_uploadedRenderables[renderable]));
    glBindVertexArray(0);
}

void GLRenderingDelegate::UploadRenderable(Renderable* renderable)
{
    GLuint vao, vbo, ibo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    auto vertexDataSize = static_cast<GLfloat>(
        renderable->GetVertexData().GetPositions().size() * sizeof(GLfloat) *
        3.0f);
    glBufferData(
        GL_ARRAY_BUFFER, vertexDataSize,
        &(renderable->GetVertexData().GetPositions())[0], GL_STATIC_DRAW);

    auto vertexDecl = renderable->GetVertexDeclaration();
    for(auto const& vertexDeclSection : vertexDecl.GetSections())
    {
        auto attribLocation =
            glGetAttribLocation(0, vertexDeclSection.m_attributeName.c_str());
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(
            attribLocation, vertexDeclSection.m_numElements, GL_FLOAT, GL_FALSE,
            vertexDeclSection.m_stride,
            (const GLvoid*)vertexDeclSection.m_offset);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    auto indexDataSize =
        renderable->GetIndexData().GetIndices().size() * sizeof(GLuint);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indexDataSize,
        &(renderable->GetIndexData().GetIndices()[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_uploadedRenderables.insert(
        std::make_pair(renderable, std::make_tuple(vao, vbo, ibo)));
}

} // namespace Fire
