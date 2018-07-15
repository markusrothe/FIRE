#include "rendererFactory.h"
#include "glRenderingDelegate.h"
#include "renderingDelegate.h"
#include "textureBinder.h"

#include <utility>

namespace Fire
{
namespace RendererFactory
{
std::unique_ptr<Renderer> CreateRenderer()
{
    std::unique_ptr<Fire::RenderingDelegate> renderingDelegate =
        std::make_unique<GLRenderingDelegate>();
    std::unique_ptr<Fire::Binder> texBinder = std::make_unique<TextureBinder>();
    std::unique_ptr<Fire::Binder> materialBinder =
        std::make_unique<TextureBinder>();

    return std::make_unique<Renderer>(
        std::move(renderingDelegate), std::move(texBinder),
        std::move(materialBinder));
}
} // namespace RendererFactory

} // namespace Fire
