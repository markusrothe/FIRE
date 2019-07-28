#include "GLImageTextureFactory.h"
namespace FIRE
{
Texture GLImageTextureFactory::CreateTexture(uint32_t width, uint32_t height, std::vector<uint8_t> data)
{
    return Texture(width, height, std::move(data));
}
} // namespace FIRE
