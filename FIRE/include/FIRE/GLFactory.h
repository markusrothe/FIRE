#ifndef FIRE_GLFactory_H
#define FIRE_GLFactory_H
#include <memory>

namespace FIRE
{

class Window;
class Renderer;
class RenderContext;

namespace GLFactory
{
std::unique_ptr<RenderContext> CreateRenderContext(Window& window);
std::unique_ptr<Renderer> CreateRenderer();
} // namespace GLFactory

} // namespace FIRE

#endif // !FIRE_GLFactory_H
