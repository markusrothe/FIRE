#ifndef FIRE_FontCharacter_h
#define FIRE_FontCharacter_h

#include <FIRE/Texture.h>
#include <FIRE/glmfwd.h>
#include <cstdint>

namespace FIRE
{
struct FontCharacter
{
    FontCharacter() = default;
    
    FontCharacter(FIRE::Texture texture, glm::ivec2 size, glm::ivec2 bearing, uint32_t advance)
        : texture(std::move(texture))
        , size(size)
        , bearing(bearing)
        , advance(advance)
    {
    }

    FontCharacter(FontCharacter&& other) noexcept
        : texture(std::move(other.texture))
        , size(other.size)
        , bearing(other.bearing)
        , advance(other.advance)
    {
    }

    FontCharacter& operator=(FontCharacter&& other) noexcept
    {
        texture = std::move(other.texture);
        std::swap(size, other.size);
        std::swap(bearing, other.bearing);
        std::swap(advance, other.advance);
        return *this;
    }

    Texture texture;      // ID handle of the glyph texture
    glm::ivec2 size{};    // Size of glyph
    glm::ivec2 bearing{}; // Offset from baseline to left/top of glyph
    uint32_t advance{};   // Offset to advance to next glyph
};
} // namespace FIRE

#endif // FIRE_FontCharacter_h