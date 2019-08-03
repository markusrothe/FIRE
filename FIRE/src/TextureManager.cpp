#include "TextureManager.h"
#include "TextureFactory.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <FIRE/glmfwd.h>
#include <iostream>

namespace FIRE
{
TextureManager::TextureManager(std::unique_ptr<TextureFactory> texFactory)
    : m_texFactory(std::move(texFactory))
{
    //    FT_Library ft;
    //    FT_Face face;
    //
    //    if(FT_Init_FreeType(&ft))
    //    {
    //        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    //    }
    //
    //    if(FT_New_Face(ft, "RussoOne-Regular.ttf", 0, &face))
    //    {
    //        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    //    }
    //
    //    FT_Set_Pixel_Sizes(face, 0, 48);
    //
    //    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    //
    //    for(GLubyte c = 0; c < 128; c++)
    //    {
    //        // Load character glyph
    //        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
    //        {
    //            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
    //            continue;
    //        }
    //        // Generate texture
    //        auto const width = face->glyph->bitmap.width;
    //        auto const height = face->glyph->bitmap.rows;
    //        if(width > 0 && height > 0)
    //        {
    //            FIRE::Texture2D texture(width, height, std::vector<uint8_t>(face->glyph->bitmap.buffer, face->glyph->bitmap.buffer + width * height));
    //
    //            // Now store character for later use
    //            FontCharacter character = {
    //                std::move(texture),
    //                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
    //                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
    //                (GLuint)face->glyph->advance.x};
    //
    //            m_characters.insert(std::make_pair(static_cast<GLchar>(c), std::move(character)));
    //        }
    //    }
    //    FT_Done_Face(face);
    //    FT_Done_FreeType(ft);
}

TextureManager::~TextureManager() = default;

FontCharacter TextureManager::CreateFontCharTexture(char c)
{
    auto it = m_characters.find(c);
    if(it == m_characters.end())
    {
        //TODO: Create FontCharTexture
        return FontCharacter();
    }
    return (it->second);
}

Texture2D* TextureManager::CreateImageTexture(uint32_t width, uint32_t height, std::vector<uint8_t> const& data)
{
    return m_texFactory->Create2DTexture(width, height, data);
}

} // namespace FIRE
