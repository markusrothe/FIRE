#ifndef FIRE_TextureManager_h
#define FIRE_TextureManager_h

#include <FIRE/FontCharacter.h>
#include <FIRE/Texture2D.h>
#include <map>
#include <memory>
#include <string>

namespace FIRE
{
class TextureFactory;
class FontLoader;
class TextureManager
{
public:
    explicit TextureManager(
        std::unique_ptr<TextureFactory> texFactory,
        std::unique_ptr<FontLoader> fontLoader);

    ~TextureManager();

    Texture2D* CreateImageTexture(
        std::string name,
        uint32_t width,
        uint32_t height,
        std::vector<uint8_t> const& data,
        uint8_t numComponents,
        Texture2D::WrappingMode wrappingMode,
        Texture2D::Filter filter);

    FontCharacter* CreateFontCharTexture(char c);

private:
    FontCharacter CreateFontCharacter(char c);

    std::unique_ptr<TextureFactory> m_texFactory;
    std::unique_ptr<FontLoader> m_fontLoader;
    std::map<char, FontCharacter> m_characters{};
    std::map<std::string, std::unique_ptr<Texture2D>> m_textures{};
};
} // namespace FIRE

#endif // FIRE_TextureManager_h
