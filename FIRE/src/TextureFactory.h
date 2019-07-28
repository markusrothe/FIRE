#ifndef FIRE_TextureFactory_h
#define FIRE_TextureFactory_h

#include <FIRE/Texture.h>
#include <memory>
#include <vector>

namespace FIRE
{
class FontTextureFactory;
class ImageTextureFactory;
struct FontCharacter;
class TextureFactory
{
public:
    TextureFactory(
        std::unique_ptr<ImageTextureFactory> imageTexFactory,
        std::unique_ptr<FontTextureFactory> fontTexFactory);

    ~TextureFactory();

    Texture CreateImageTexture(uint32_t width, uint32_t height, std::vector<uint8_t> data);
    FontCharacter* CreateFontCharTexture(char c);

private:
    std::unique_ptr<ImageTextureFactory> m_imageTexFactory;
    std::unique_ptr<FontTextureFactory> m_fontTexFactory;
};
} // namespace FIRE

#endif // FIRE_TextureFactory_h