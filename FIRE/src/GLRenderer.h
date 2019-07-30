#ifndef FIRE_GLRenderer_h
#define FIRE_GLRenderer_h

#include <FIRE/Renderer.h>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
namespace FIRE
{
class Uploader;
class DrawAgent;
class Scene;
struct Renderable;
class TextureFactory;
class StaticGeometryRenderer;

class GLRenderer : public Renderer
{
public:
    explicit GLRenderer(
        std::unique_ptr<StaticGeometryRenderer> staticGeometryRenderer,
        std::unique_ptr<TextureFactory> texFactory);

    ~GLRenderer() override;

    void Submit(Renderable const& renderable) override;
    void Submit(TextOverlay overlay) override;

    void Render(float windowWidth, float windowHeight) override;

    void ToggleWireframe() override;

private:
    void Render(TextOverlay const& overlay, float width, float height);
    std::map<std::string, Renderable> m_renderables;
    std::map<int, TextOverlay> m_overlays;

    std::unique_ptr<StaticGeometryRenderer> m_staticGeometryRenderer;

    std::unique_ptr<TextureFactory> m_texFactory;
    uint32_t texVAO, texVBO;
    uint32_t m_texShader;
};
} // namespace FIRE

#endif // !FIRE_GLRenderer_h
