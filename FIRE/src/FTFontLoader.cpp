#include "FTFontLoader.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <FIRE/glmfwd.h>
#include <stdexcept>
namespace FIRE
{
FontCharacter FTFontLoader::LoadChar(char c)
{
    FT_Library ft;
    FT_Face face;

    if(FT_Init_FreeType(&ft))
    {
        throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
    }

    if(FT_New_Face(ft, "RussoOne-Regular.ttf", 0, &face))
    {
        throw std::runtime_error("ERROR::FREETYPE: Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    // Load character glyph
    if(FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
        throw std::runtime_error("ERROR::FREETYTPE: Failed to load Glyph");
    }

    FontCharacter fontChar{
        nullptr,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        static_cast<uint32_t>(face->glyph->advance.x),
        std::vector<uint8_t>(
            face->glyph->bitmap.buffer,
            face->glyph->bitmap.buffer + face->glyph->bitmap.width * face->glyph->bitmap.rows)};

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return fontChar;
}
} // namespace FIRE
