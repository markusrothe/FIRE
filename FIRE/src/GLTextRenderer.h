#ifndef FIRE_GLTextRenderer_h
#define FIRE_GLTextRenderer_h

#include <FIRE/TextOverlay.h>
#include <FIRE/TextRenderer.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace FIRE
{
class TextureFactory;
class GLTextRenderer : public TextRenderer
{
public:
    explicit GLTextRenderer(std::unique_ptr<TextureFactory> texFactory);
    ~GLTextRenderer();

    void Render(float windowWidth, float windowHeight) override;
    void Submit(TextOverlay overlay) override;

private:
    void Render(TextOverlay const& overlay, float width, float height);

    std::vector<TextOverlay> m_renderables;
    std::unique_ptr<TextureFactory> m_texFactory;
    uint32_t texVAO, texVBO;
    uint32_t m_texShader;
};
} // namespace FIRE

#endif // FIRE_GLTextRenderer_h