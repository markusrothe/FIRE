#ifndef FIRE_GLRenderer_h
#define FIRE_GLRenderer_h

#include <FIRE/Renderer.h>
#include <map>
#include <memory>
#include <string>
namespace FIRE
{
class Uploader;
class DrawAgent;
class Scene;
struct Renderable;

class GLRenderer : public Renderer
{
public:
    explicit GLRenderer(
        std::unique_ptr<Uploader> uploader,
        std::unique_ptr<DrawAgent> drawAgent);

    ~GLRenderer() override;

    void Submit(Renderable const& renderable) override;
    void Render(float windowWidth, float windowHeight) override;

    void ToggleWireframe() override;

private:
    std::map<std::string, Renderable> m_renderables;

    std::unique_ptr<Uploader> m_uploader;
    std::unique_ptr<DrawAgent> m_drawAgent;
};
} // namespace FIRE

#endif // !FIRE_GLRenderer_h
