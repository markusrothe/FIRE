#include <FIRE/Texture.h>
#include <glad/glad.h>
#include <utility>
#include <vector>

namespace FIRE
{

Texture::Texture(uint32_t width, uint32_t height, std::vector<uint8_t> data)
    : m_width(width)
    , m_height(height)
    , m_data(std::move(data))
{
    glGenTextures(1, &m_id);

    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, m_data.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Release();
}
Texture::~Texture()
{
    if(m_id != 0u)
    {
        glDeleteTextures(1u, &m_id);
    }
}

uint32_t Texture::Id() const
{
    return m_id;
}

uint32_t Texture::Width() const
{
    return m_width;
}

uint32_t Texture::Height() const
{
    return m_height;
}

std::vector<uint8_t> const& Texture::Data() const
{
    return m_data;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Release()
{
    glBindTexture(GL_TEXTURE_2D, 0u);
}
Texture::Texture(Texture&& other) noexcept
    : m_width(0u)
    , m_height(0u)
    , m_id(0u)
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_id, other.m_id);
    std::swap(m_data, other.m_data);
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_id, other.m_id);
    std::swap(m_data, other.m_data);
    return *this;
}
} // namespace FIRE
