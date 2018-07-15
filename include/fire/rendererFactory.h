#ifndef fire_rendererfactory_h
#define fire_rendererfactory_h

#include "renderer.h"
#include <memory>

namespace Fire
{
namespace RendererFactory
{
std::unique_ptr<Renderer> CreateRenderer();

} // namespace RendererFactory
} // namespace Fire

#endif // fire_rendererfactory_h
