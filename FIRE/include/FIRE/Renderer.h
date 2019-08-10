#ifndef FIRE_Renderer_h
#define FIRE_Renderer_h

#include <map>
#include <memory>
#include <string>

namespace FIRE
{
struct Renderable;
class TextOverlay;
class AssetFacade;
class MaterialBinder;
class VertexLayoutFactory;
class Draw;
class Renderer
{
public:
    explicit Renderer(
        std::unique_ptr<Draw> draw,
        std::unique_ptr<MaterialBinder> materialBinder,
        std::unique_ptr<VertexLayoutFactory> vertexLayoutFactory,
        std::shared_ptr<AssetFacade> assets);

    ~Renderer();

    void Submit(Renderable const& renderable);
    void Submit(TextOverlay const& overlay);

    void Render(float windowWidth, float windowHeight);

    void ToggleWireframe();

private:
    void Render(Renderable renderable);
    void Render(TextOverlay overlay, float width, float height);

    std::unique_ptr<Draw> m_draw;
    std::unique_ptr<MaterialBinder> m_materialBinder;
    std::unique_ptr<VertexLayoutFactory> m_vertexLayoutFactory;
    std::shared_ptr<AssetFacade> m_assets;

    std::map<std::string, Renderable> m_renderables;
    std::map<std::string, TextOverlay> m_overlays;
};
} // namespace FIRE

#endif // !FIRE_Renderer_h
