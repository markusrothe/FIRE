#ifndef FIRE_Texture_h
#define FIRE_Texture_h

#include <cstdint>
#include <memory>
#include <vector>

namespace FIRE
{
class Texture
{
public:
    Texture() = default;
    Texture(uint32_t width, uint32_t height, std::vector<uint8_t> data);

    Texture(Texture const&) = delete;
    Texture& operator=(Texture const&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    ~Texture();

    [[nodiscard]] uint32_t Id() const;
    [[nodiscard]] uint32_t Width() const;
    [[nodiscard]] uint32_t Height() const;
    [[nodiscard]] std::vector<uint8_t> const& Data() const;

    void Bind();
    void Release();

private:
    uint32_t m_width;
    uint32_t m_height;
    std::vector<uint8_t> m_data;
    uint32_t m_id{};
};
} // namespace FIRE

#endif
