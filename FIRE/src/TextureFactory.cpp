#include "TextureFactory.h"
#include "FontTextureFactory.h"
#include "ImageTextureFactory.h"

namespace FIRE
{
TextureFactory::TextureFactory(std::unique_ptr<ImageTextureFactory> imageTexFactory, std::unique_ptr<FontTextureFactory> fontTexFactory)
    : m_imageTexFactory(std::move(imageTexFactory))
    , m_fontTexFactory(std::move(fontTexFactory))
{
}

TextureFactory::~TextureFactory() = default;

FontCharacter* TextureFactory::CreateFontCharTexture(char c)
{
    return m_fontTexFactory->CreateTexture(c);
}

Texture TextureFactory::CreateImageTexture(uint32_t width, uint32_t height, std::vector<uint8_t> data)
{
    return m_imageTexFactory->CreateTexture(width, height, std::move(data));
}

} // namespace FIRE
