#include <FIRE/Texture2D.h>
#include <glad/glad.h>
#include <utility>
#include <vector>

namespace FIRE
{

Texture2D::Texture2D(uint32_t width, uint32_t height, std::vector<uint8_t> data)
    : m_width(width)
    , m_height(height)
    , m_data(std::move(data))
{

    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    glTextureStorage2D(m_id, 1, GL_R8, width, height);
    glTextureSubImage2D(m_id, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, m_data.data());
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
Texture2D::~Texture2D()
{
    if(m_id != 0u)
    {
        glDeleteTextures(1u, &m_id);
    }
}

uint32_t Texture2D::Id() const
{
    return m_id;
}

uint32_t Texture2D::Width() const
{
    return m_width;
}

uint32_t Texture2D::Height() const
{
    return m_height;
}

std::vector<uint8_t> const& Texture2D::Data() const
{
    return m_data;
}

void Texture2D::Bind(uint32_t unit)
{
    glBindTextureUnit(unit, m_id);
}

void Texture2D::Release()
{
    glBindTextureUnit(0u, m_id);
}
Texture2D::Texture2D(Texture2D&& other) noexcept
    : m_width(0u)
    , m_height(0u)
    , m_id(0u)
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_id, other.m_id);
    std::swap(m_data, other.m_data);
}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_id, other.m_id);
    std::swap(m_data, other.m_data);
    return *this;
}
} // namespace FIRE
