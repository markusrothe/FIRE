#include "GLFontTextureFactory.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <FIRE/Texture.h>
#include <iostream>
namespace FIRE
{
GLFontTextureFactory::GLFontTextureFactory()
{
    FT_Library ft;
    FT_Face face;

    if(FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    if(FT_New_Face(ft, "RussoOne-Regular.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for(GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        auto const width = face->glyph->bitmap.width;
        auto const height = face->glyph->bitmap.rows;
        FIRE::Texture texture(width, height, std::vector<uint8_t>(face->glyph->bitmap.buffer, face->glyph->bitmap.buffer + width * height));

        // Now store character for later use
        FontCharacter character = {
            std::move(texture),
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (GLuint)face->glyph->advance.x};

        m_characters.insert(std::make_pair(static_cast<GLchar>(c), std::move(character)));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

FontCharacter* GLFontTextureFactory::CreateTexture(char c)
{
    auto it = m_characters.find(c);
    if(it == m_characters.end())
    {
        return nullptr;
    }
    return &(it->second);
}
} // namespace FIRE
