#ifndef FIRE_GLTEXTUREFACTORY_H
#define FIRE_GLTEXTUREFACTORY_H

#include "TextureFactory.h"
#include <string>

namespace FIRE
{
class GLTextureFactory : public TextureFactory
{
public:
    std::unique_ptr<Texture2D> Load(std::string const& filepath, Texture2D::WrappingMode wrappingMode) override;
    FontCharacter LoadFontCharacter(char c) override;
    std::unique_ptr<Texture2D> Create2DTexture(
        uint32_t width,
        uint32_t height,
        std::vector<uint8_t> const& data,
        uint8_t numComponents,
        Texture2D::WrappingMode wrappingMode,
        Texture2D::Filter filter) override;
};
} // namespace FIRE

#endif // FIRE_GLTEXTUREFACTORY_H
