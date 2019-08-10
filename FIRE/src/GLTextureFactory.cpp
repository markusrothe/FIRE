#include "GLTextureFactory.h"
#include "GLTexture2D.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <FIRE/glmfwd.h>
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
namespace FIRE
{
std::unique_ptr<Texture2D> GLTextureFactory::Load(std::string const& filepath, Texture2D::WrappingMode wrappingMode)
{
    int width, height, numComponents;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &numComponents, 0);
    if(data)
    {
        std::vector<uint8_t> pixels(data, data + (height * width * numComponents));
        stbi_image_free(data);
        return Create2DTexture(width, height, pixels, static_cast<uint8_t>(numComponents), wrappingMode, FIRE::Texture2D::Filter::LINEAR);
    }
    return nullptr;
}

std::unique_ptr<Texture2D> GLTextureFactory::Create2DTexture(
    uint32_t width,
    uint32_t height,
    std::vector<uint8_t> const& data,
    uint8_t numComponents,
    Texture2D::WrappingMode wrappingMode,
    Texture2D::Filter filter)
{
    return std::make_unique<GLTexture2D>(width, height, data, numComponents, wrappingMode, filter);
}

FontCharacter GLTextureFactory::LoadFontCharacter(char c)
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
