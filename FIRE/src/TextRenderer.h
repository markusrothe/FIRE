#ifndef FIRE_TextRenderer_h
#define FIRE_TextRenderer_h

namespace FIRE
{
class TextOverlay;
class TextRenderer
{
public:
    virtual ~TextRenderer() = default;
    virtual void Render(TextOverlay overlay, float windowWidth, float windowHeight) = 0;
};
} // namespace FIRE

#endif // FIRE_TextRenderer_h