#ifndef FIRE_RendererImpl_h
#define FIRE_RendererImpl_h

#include <FIRE/Renderer.h>
#include <memory>
namespace FIRE
{
class Uploader;
class DrawAgent;
class Scene;
class TextOverlay;
class TextRenderer;

class RendererImpl : public Renderer
{
public:
    explicit RendererImpl(
        std::unique_ptr<Uploader> uploader,
        std::unique_ptr<DrawAgent> drawAgent,
        std::unique_ptr<TextRenderer> textRenderer);

    ~RendererImpl() override;

    void Render(Scene const& scene, float windowWidth, float windowHeight) override;

private:
    std::unique_ptr<Uploader> m_uploader;
    std::unique_ptr<DrawAgent> m_drawAgent;
    std::unique_ptr<TextRenderer> m_textRenderer;
};
} // namespace FIRE

#endif // !FIRE_RendererImpl_h
