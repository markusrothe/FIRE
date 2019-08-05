#ifndef FIRE_FontCharacter_h
#define FIRE_FontCharacter_h

#include <FIRE/Texture2D.h>
#include <FIRE/glmfwd.h>
#include <cstdint>
#include <vector>

namespace FIRE
{
struct FontCharacter
{
    FontCharacter() = default;

    FontCharacter(std::unique_ptr<Texture2D> texture, glm::ivec2 size, glm::ivec2 bearing, uint32_t advance, std::vector<uint8_t> data)
        : texture(std::move(texture))
        , size(size)
        , bearing(bearing)
        , advance(advance)
        , data(std::move(data))
    {
    }

    FontCharacter(FontCharacter&&) = default;
    FontCharacter& operator=(FontCharacter&&) = default;

    std::unique_ptr<Texture2D> texture{}; // ID handle of the glyph texture
    glm::ivec2 size{};                    // Size of glyph
    glm::ivec2 bearing{};                 // Offset from baseline to left/top of glyph
    uint32_t advance{};                   // Offset to advance to next glyph
    std::vector<uint8_t> data{};
};
} // namespace FIRE

#endif // FIRE_FontCharacter_h
