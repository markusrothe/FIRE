#ifndef FIRE_GLTextRenderer_h
#define FIRE_GLTextRenderer_h

#include "TextRenderer.h"
#include <cstdint>
#include <memory>

namespace FIRE
{
class TextOverlay;
class TextureFactory;
class GLTextRenderer : public TextRenderer
{
public:
    explicit GLTextRenderer(std::unique_ptr<TextureFactory> texFactory);
    ~GLTextRenderer();
    void Render(TextOverlay overlay);

private:
    std::unique_ptr<TextureFactory> m_texFactory;
    uint32_t m_texShader;
};
} // namespace FIRE

#endif // FIRE_GLTextRenderer_h