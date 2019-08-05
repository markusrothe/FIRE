#ifndef FIRE_GLFactory_H
#define FIRE_GLFactory_H
#include <FIRE/MaterialFactory.h>
#include <cstdint>
#include <memory>
#include <string>
namespace FIRE
{

class Window;
class Renderer;
class RenderContext;
class ShaderFactory;
class MeshManager;
class TextureManager;

namespace GLFactory
{
Window InitWindow(std::string title, uint32_t width, uint32_t height);
std::unique_ptr<RenderContext> CreateRenderContext(Window& window);
std::unique_ptr<TextureManager> CreateTextureManager();
MaterialFactory CreateMaterialFactory();
std::unique_ptr<Renderer> CreateRenderer(std::shared_ptr<TextureManager> texManager);

} // namespace GLFactory

} // namespace FIRE

#endif // !FIRE_GLFactory_H
