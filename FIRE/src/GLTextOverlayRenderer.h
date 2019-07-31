#ifndef FIRE_GLTEXTOVERLAYRENDERER_H
#define FIRE_GLTEXTOVERLAYRENDERER_H

#include "TextOverlayRenderer.h"
#include <cstdint>
#include <memory>
namespace FIRE
{
class TextureFactory;
class GLTextOverlayRenderer : public TextOverlayRenderer
{
public:
    explicit GLTextOverlayRenderer(std::unique_ptr<TextureFactory> texFactory);
    ~GLTextOverlayRenderer() override;
    void Render(TextOverlay const& overlay, float windowWidth, float windowHeight) override;

private:
    std::unique_ptr<TextureFactory> m_texFactory;
    uint32_t texVAO, texVBO;
    uint32_t m_texShader;
};
} // namespace FIRE

#endif //FIRE_GLTEXTOVERLAYRENDERER_H
