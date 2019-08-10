#ifndef FIRE_GLFactory_H
#define FIRE_GLFactory_H
#include <cstdint>
#include <memory>
#include <string>
namespace FIRE
{

class Window;
class Renderer;
class RenderContext;
class ShaderFactory;

namespace GLFactory
{
Window InitWindow(std::string title, uint32_t width, uint32_t height);
std::shared_ptr<AssetFacade> CreateAssetFacade();
std::unique_ptr<RenderContext> CreateRenderContext(Window& window);
std::unique_ptr<Renderer> CreateRenderer(std::shared_ptr<AssetFacade> assets);

} // namespace GLFactory

} // namespace FIRE

#endif // !FIRE_GLFactory_H
