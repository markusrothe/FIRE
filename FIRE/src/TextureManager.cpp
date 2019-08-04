#include "FIRE/TextureManager.h"
#include "FontLoader.h"
#include "TextureFactory.h"
#include <FIRE/glmfwd.h>
#include <iostream>
#include <stdexcept>
#include <xutility>

namespace FIRE
{

TextureManager::TextureManager(std::unique_ptr<TextureFactory> texFactory, std::unique_ptr<FontLoader> fontLoader)
    : m_texFactory(std::move(texFactory))
    , m_fontLoader(std::move(fontLoader))
{
}

TextureManager::~TextureManager() = default;

FontCharacter* TextureManager::CreateFontCharTexture(char c)
{
    auto it = m_characters.find(c);
    if(it == m_characters.end())
    {
        auto inserted = m_characters.insert(std::make_pair(c, CreateFontCharacter(c)));
        return &(inserted.first->second);
    }

    return &(it->second);
}

Texture2D* TextureManager::CreateImageTexture(std::string name, uint32_t width, uint32_t height, std::vector<uint8_t> const& data)
{
    if(auto it = m_textures.find(name); it != m_textures.end())
    {
        return it->second.get();
    }

    auto tex = m_texFactory->Create2DTexture(width, height, data);
    auto inserted = m_textures.insert(std::make_pair(std::move(name), std::move(tex)));
    if(!inserted.second)
    {
        throw std::runtime_error("Could not cache texture.");
    }

    return inserted.first->second.get();
}

FontCharacter TextureManager::CreateFontCharacter(char c)
{
    FontCharacter fontChar;

    try
    {
        fontChar = m_fontLoader->LoadChar(c);
    }
    catch(std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }

    auto width = fontChar.size.x;
    auto height = fontChar.size.y;

    if(width > 0 && height > 0)
    {
        fontChar.texture = m_texFactory->Create2DTexture(width, height, fontChar.data);
    }

    return fontChar;
}

} // namespace FIRE
