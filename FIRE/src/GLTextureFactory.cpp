#include "GLTextureFactory.h"
#include "GLTexture2D.h"

namespace FIRE
{
std::unique_ptr<Texture2D> GLTextureFactory::Create2DTexture(
    uint32_t width,
    uint32_t height,
    std::vector<uint8_t> const& data,
    uint8_t numComponents,
    Texture2D::WrappingMode wrappingMode,
    Texture2D::Filter filter)
{
    return std::make_unique<GLTexture2D>(width, height, data, numComponents, wrappingMode, filter);
}
} // namespace FIRE
