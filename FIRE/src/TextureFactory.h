#ifndef FIRE_TEXTUREFACTORY_H
#define FIRE_TEXTUREFACTORY_H

#include <FIRE/FontCharacter.h>
#include <FIRE/Texture2D.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
namespace FIRE
{

class TextureFactory
{
public:
    virtual ~TextureFactory() = default;

    virtual std::unique_ptr<Texture2D> Load(std::string const& filepath, Texture2D::WrappingMode wrappingMode) = 0;

    virtual std::unique_ptr<Texture2D> Create2DTexture(
        uint32_t width,
        uint32_t height,
        std::vector<uint8_t> const& data,
        uint8_t numComponents,
        Texture2D::WrappingMode wrappingMode,
        Texture2D::Filter filter) = 0;

    virtual FontCharacter LoadFontCharacter(char c) = 0;
};
} // namespace FIRE

#endif // FIRE_TEXTUREFACTORY_H
