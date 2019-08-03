#ifndef FIRE_Renderer_h
#define FIRE_Renderer_h

#include <map>
#include <memory>
#include <string>

namespace FIRE
{
struct Renderable;
class TextOverlay;
class TextureManager;
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
        std::unique_ptr<TextureManager> texFactory);

    ~Renderer();

    void Submit(Renderable const& renderable);
    void Submit(TextOverlay const& overlay);

    void Render(float windowWidth, float windowHeight);

    void ToggleWireframe();

private:
    void Render(Renderable const& renderable);
    void Render(TextOverlay const& overlay, float width, float height);

    std::unique_ptr<Draw> m_draw;
    std::unique_ptr<MaterialBinder> m_materialBinder;
    std::unique_ptr<VertexLayoutFactory> m_vertexLayoutFactory;
    std::unique_ptr<TextureManager> m_texManager;

    std::map<std::string, Renderable> m_renderables;
    std::map<std::string, TextOverlay> m_overlays;
};
} // namespace FIRE

#endif // !FIRE_Renderer_h
