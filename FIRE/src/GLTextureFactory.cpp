#include "GLTextureFactory.h"

namespace FIRE
{
Texture2D* GLTextureFactory::Create2DTexture(uint32_t, uint32_t, std::vector<uint8_t> const&)
{
    return nullptr;
}
} // namespace FIRE
