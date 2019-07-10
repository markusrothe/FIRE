#ifndef FIRE_RendererImpl_h
#define FIRE_RendererImpl_h

#include <FIRE/Renderer.h>
#include <memory>
#include <vector>
namespace FIRE
{
class Uploader;
class DrawAgent;
class Scene;
struct Renderable;

class RendererImpl : public Renderer
{
public:
    explicit RendererImpl(
        std::unique_ptr<Uploader> uploader,
        std::unique_ptr<DrawAgent> drawAgent);

    ~RendererImpl() override;

    void Submit(Renderable const& renderable) override;

    void Render(float windowWidth, float windowHeight) override;

private:
    std::vector<Renderable> m_renderables;

    std::unique_ptr<Uploader> m_uploader;
    std::unique_ptr<DrawAgent> m_drawAgent;
};
} // namespace FIRE

#endif // !FIRE_RendererImpl_h
