#include "GLTexture2D.h"
#include <algorithm>
#include <glad/glad.h>
#include <stdexcept>
#include <utility>
#include <vector>

namespace FIRE
{

std::pair<GLenum, GLenum> GetInternalFormat(uint8_t numComponents)
{
    switch(numComponents)
    {
    case 1:
        return std::make_pair(GL_R8, GL_RED);
    case 2:
        return std::make_pair(GL_RG8, GL_RG);
    case 3:
        return std::make_pair(GL_RGB8, GL_RGB);
    case 4:
        return std::make_pair(GL_RGBA8, GL_RGBA);
    default:
        throw std::runtime_error("Invalid number of components for texture");
    }
}

GLenum GetWrappingMode(Texture2D::WrappingMode wrappingMode)
{
    switch(wrappingMode)
    {
    case Texture2D::WrappingMode::CLAMP:
        return GL_CLAMP_TO_EDGE;
    case Texture2D::WrappingMode::MIRROR:
        return GL_MIRRORED_REPEAT;
    case Texture2D::WrappingMode::WRAP:
        return GL_REPEAT;
    default:
        throw std::runtime_error("Unsupported WrappingMode");
    }
}

GLenum GetMinFilter(Texture2D::Filter filter)
{
    switch(filter)
    {
    case Texture2D::Filter::LINEAR:
        return GL_NEAREST_MIPMAP_LINEAR;
    case Texture2D::Filter ::NEAREST:
        return GL_NEAREST_MIPMAP_NEAREST;
    default:
        throw std::runtime_error("Unsupported filter");
    }
}

GLenum GetMaxFilter(Texture2D::Filter filter)
{
    switch(filter)
    {
    case Texture2D::Filter::LINEAR:
        return GL_LINEAR;
    case Texture2D::Filter ::NEAREST:
        return GL_NEAREST;
    default:
        throw std::runtime_error("Unsupported filter");
    }
}

GLTexture2D::GLTexture2D(
    uint32_t width,
    uint32_t height,
    std::vector<uint8_t> data,
    uint8_t numComponents,
    Texture2D::WrappingMode wrappingMode,
    Texture2D::Filter filter)
    : m_width(width)
    , m_height(height)
    , m_data(std::move(data))
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

    auto const internalFormat = GetInternalFormat(numComponents);
    auto const wrapping = GetWrappingMode(wrappingMode);
    auto const minFilter = GetMinFilter(filter);
    auto const maxFilter = GetMaxFilter(filter);

    auto numMipMapLevels = static_cast<uint32_t>(1 + floor(log2(std::max(static_cast<double>(width), std::max(static_cast<double>(height), 1.0)))));
    glTextureStorage2D(m_id, numMipMapLevels, internalFormat.first, width, height);
    glTextureSubImage2D(m_id, 0, 0, 0, width, height, internalFormat.second, GL_UNSIGNED_BYTE, m_data.data());
    glGenerateTextureMipmap(m_id);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrapping);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrapping);
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, minFilter);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, maxFilter);
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
