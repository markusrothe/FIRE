#ifndef FIRE_FontCharacter_h
#define FIRE_FontCharacter_h

#include <FIRE/glmfwd.h>
#include <cstdint>

namespace FIRE
{
struct FontCharacter
{
    uint32_t textureID; // ID handle of the glyph texture
    glm::ivec2 size;    // Size of glyph
    glm::ivec2 bearing; // Offset from baseline to left/top of glyph
    uint32_t advance;   // Offset to advance to next glyph
};
} // namespace FIRE

#endif // FIRE_FontCharacter_h