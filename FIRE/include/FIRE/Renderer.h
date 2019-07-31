#ifndef FIRE_Renderer_h
#define FIRE_Renderer_h

#include <map>
#include <memory>
#include <string>

namespace FIRE
{
struct Renderable;
class TextOverlay;
class VertexLayoutBinder;
class MaterialBinder;
class MeshUploader;
class Draw;
class Renderer
{
public:
    explicit Renderer(
        std::unique_ptr<Draw> draw,
        std::unique_ptr<VertexLayoutBinder> vertexLayoutBinder,
        std::unique_ptr<MaterialBinder> materialBinder,
        std::unique_ptr<MeshUploader> meshUploader);

    ~Renderer();

    void Submit(Renderable const& renderable);
    void Submit(TextOverlay const& overlay);

    void Render(float windowWidth, float windowHeight);

    void ToggleWireframe();

private:
    void Render(Renderable const& renderable);

    std::unique_ptr<Draw> m_draw;
    std::unique_ptr<VertexLayoutBinder> m_vertexLayoutBinder;
    std::unique_ptr<MaterialBinder> m_materialBinder;
    std::unique_ptr<MeshUploader> m_meshUploader;

    std::map<std::string, Renderable> m_renderables;
    std::map<int, TextOverlay> m_overlays;
};
} // namespace FIRE

#endif // !FIRE_Renderer_h
