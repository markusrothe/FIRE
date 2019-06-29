#ifndef FIRE_GLFactory_H
#define FIRE_GLFactory_H
#include <memory>

namespace FIRE
{

class Window;
class Renderer;
class RenderContext;
class ShaderFactory;
class MeshManager;

namespace GLFactory
{
std::unique_ptr<RenderContext> CreateRenderContext(Window& window);
std::unique_ptr<Renderer> CreateRenderer(MeshManager& meshManager);
std::unique_ptr<ShaderFactory> CreateShaderFactory();
} // namespace GLFactory

} // namespace FIRE

#endif // !FIRE_GLFactory_H
