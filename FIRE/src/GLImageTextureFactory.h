#ifndef FIRE_GLIMAGETEXTUREFACTORY_H
#define FIRE_GLIMAGETEXTUREFACTORY_H

#include "ImageTextureFactory.h"
namespace FIRE
{
class GLImageTextureFactory : public ImageTextureFactory
{
public:
    Texture CreateTexture(uint32_t width, uint32_t height, std::vector<uint8_t> data) override;
};
} // namespace FIRE

#endif //FIRE_GLIMAGETEXTUREFACTORY_H
