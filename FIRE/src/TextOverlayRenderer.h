#ifndef FIRE_TEXTOVERLAYRENDERER_H
#define FIRE_TEXTOVERLAYRENDERER_H

namespace FIRE
{
class TextOverlay;
class TextOverlayRenderer
{
public:
    virtual ~TextOverlayRenderer() = default;
    virtual void Render(TextOverlay const& overlay, float windowWidth, float windowHeight) = 0;
};
} // namespace FIRE
#endif //FIRE_TEXTOVERLAYRENDERER_H
