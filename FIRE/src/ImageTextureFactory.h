#ifndef FIRE_ImageTextureFactory_h
#define FIRE_ImageTextureFactory_h

#include <FIRE/Texture.h>
#include <cstdint>
#include <vector>

namespace FIRE
{
class ImageTextureFactory
{
public:
    virtual ~ImageTextureFactory() = default;
    virtual Texture CreateTexture(uint32_t width, uint32_t height, std::vector<uint8_t> data) = 0;
};
} // namespace FIRE

#endif //FIRE_ImageTextureFactory_h
