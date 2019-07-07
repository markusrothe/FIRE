#ifndef FIRE_TextureFactory_h
#define FIRE_TextureFactory_h

#include <memory>
namespace FIRE
{
class FontTextureFactory;
struct FontCharacter;
class TextureFactory
{
public:
    explicit TextureFactory(std::unique_ptr<FontTextureFactory> fontTexFactory);
    ~TextureFactory();

    FontCharacter CreateFontCharTexture(char c);

private:
    std::unique_ptr<FontTextureFactory> m_fontTextFactory;
};
} // namespace FIRE

#endif // FIRE_TextureFactory_h