#include "TextureFactory.h"
#include "FontTextureFactory.h"

namespace FIRE
{
TextureFactory::TextureFactory(std::unique_ptr<FontTextureFactory> fontTexFactory)
    : m_fontTextFactory(std::move(fontTexFactory))
{
}

TextureFactory::~TextureFactory() = default;

FontCharacter TextureFactory::CreateFontCharTexture(char c)
{
    return m_fontTextFactory->CreateTexture(c);
}

} // namespace FIRE
