#ifndef FIRE_TextureManager_h
#define FIRE_TextureManager_h

#include "FontCharacter.h"
#include <map>
#include <memory>

namespace FIRE
{
class Texture2D;
class TextureFactory;
class TextureManager
{
public:
    explicit TextureManager(std::unique_ptr<TextureFactory> texFactory);

    ~TextureManager();

    Texture2D* CreateImageTexture(uint32_t width, uint32_t height, std::vector<uint8_t> const& data);
    FontCharacter CreateFontCharTexture(char c);

private:
    std::unique_ptr<TextureFactory> m_texFactory;
    std::map<char, FontCharacter> m_characters{};
};
} // namespace FIRE

#endif // FIRE_TextureManager_h