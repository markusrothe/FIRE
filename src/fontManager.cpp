#include "fontManager.h"
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace blocks
{
    FontManager::FontManager()
        : m_charTextures()
    {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library.\n";
        }

        FT_Face face;
        if (FT_New_Face(ft, "fonts/FreeSerif.ttf", 0, &face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font.\n";
        }

        // TODO: magic numbers!
        FT_Set_Pixel_Sizes(face, 0, 30);

        for (unsigned int i = 0; i < 128; ++i)
        {
            if (FT_Load_Char(face, i, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYPE: Failed to load glyph.\n";
                continue;
            }

            m_charTextures.insert(
                std::make_pair(
                    static_cast<char>(i)
                    , CharTexture(face->glyph->bitmap.width, face->glyph->bitmap.rows
                        , face->glyph->bitmap_left, face->glyph->bitmap_top
                        , face->glyph->advance.x, face->glyph->bitmap.buffer)));

        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
  
    CharTexture* FontManager::GetCharTexture(char c)
    {
        auto it = m_charTextures.find(c);

        return (it != m_charTextures.end()) ? &(it->second) : nullptr;
    }
}
