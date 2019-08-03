#ifndef FIRE_Texture_h
#define FIRE_Texture_h

#include <cstdint>
#include <memory>
#include <vector>

namespace FIRE
{
class Texture2D
{
public:
    Texture2D() = default;
    Texture2D(uint32_t width, uint32_t height, std::vector<uint8_t> data);

    Texture2D(Texture2D const&) = delete;
    Texture2D& operator=(Texture2D const&) = delete;
    Texture2D(Texture2D&& other) noexcept;
    Texture2D& operator=(Texture2D&& other) noexcept;

    ~Texture2D();

    [[nodiscard]] uint32_t Id() const;
    [[nodiscard]] uint32_t Width() const;
    [[nodiscard]] uint32_t Height() const;
    [[nodiscard]] std::vector<uint8_t> const& Data() const;

    void Bind(uint32_t unit);
    void Release();

private:
    uint32_t m_width;
    uint32_t m_height;
    std::vector<uint8_t> m_data;
    uint32_t m_id{};
};
} // namespace FIRE

#endif
