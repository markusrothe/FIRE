#include "rendererFactory.h"
#include "glRenderingDelegate.h"
#include "renderingDelegate.h"

#include <utility>

namespace Fire
{
namespace RendererFactory
{
std::unique_ptr<Renderer> CreateRenderer()
{
    std::unique_ptr<Fire::RenderingDelegate> renderingDelegate =
        std::make_unique<GLRenderingDelegate>();

    return std::make_unique<Renderer>(std::move(renderingDelegate));
}
} // namespace RendererFactory

} // namespace Fire
