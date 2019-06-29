#ifndef FIRE_GLFactory_H
#define FIRE_GLFactory_H
#include <memory>

namespace FIRE
{

class Window;
class Renderer;
class RenderContext;
class ShaderFactory;
class MeshFactory;

namespace GLFactory
{
std::unique_ptr<RenderContext> CreateRenderContext(Window& window);
std::unique_ptr<Renderer> CreateRenderer(MeshFactory& meshFactory);
std::unique_ptr<ShaderFactory> CreateShaderFactory();
} // namespace GLFactory

} // namespace FIRE

#endif // !FIRE_GLFactory_H
