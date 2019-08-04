#include "GLTexture2D.h"
#include <glad/glad.h>
#include <utility>
#include <vector>

namespace FIRE
{

GLTexture2D::GLTexture2D(uint32_t width, uint32_t height, std::vector<uint8_t> data)
    : m_width(width)
    , m_height(height)
    , m_data(std::move(data))
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    glTextureStorage2D(m_id, 1, GL_R8, width, height);
    glTextureSubImage2D(m_id, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, m_data.data());
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

GLTexture2D::~GLTexture2D()
{
    if(m_id != 0u)
    {
        glDeleteTextures(1u, &m_id);
    }
}

uint32_t GLTexture2D::Id() const
{
    return m_id;
}

uint32_t GLTexture2D::Width() const
{
    return m_width;
}

uint32_t GLTexture2D::Height() const
{
    return m_height;
}

std::vector<uint8_t> const& GLTexture2D::Data() const
{
    return m_data;
}

void GLTexture2D::Bind(uint32_t unit)
{
    glBindTextureUnit(unit, m_id);
}

void GLTexture2D::Release()
{
    glBindTextureUnit(0u, m_id);
}

} // namespace FIRE
