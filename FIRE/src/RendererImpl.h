#ifndef FIRE_RendererImpl_h
#define FIRE_RendererImpl_h

#include <FIRE/Renderer.h>
#include <memory>
namespace FIRE
{
class Uploader;
class DrawAgent;

class RendererImpl : public Renderer
{
public:
    explicit RendererImpl(
        std::unique_ptr<Uploader> uploader,
        std::unique_ptr<DrawAgent> drawAgent);

    ~RendererImpl() override;

    void Render(Renderable const& renderable) override;

private:
    std::unique_ptr<Uploader> m_uploader;
    std::unique_ptr<DrawAgent> m_drawAgent;
};
} // namespace FIRE

#endif // !FIRE_RendererImpl_h
