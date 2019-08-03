#ifndef FIRE_TEXTUREFACTORY_H
#define FIRE_TEXTUREFACTORY_H

#include <cstdint>
#include <vector>
namespace FIRE
{
class Texture2D;
class TextureFactory
{
public:
    virtual ~TextureFactory() = default;
    virtual Texture2D* Create2DTexture(uint32_t width, uint32_t height, std::vector<uint8_t> const& data) = 0;
};
} // namespace FIRE

#endif //FIRE_TEXTUREFACTORY_H
