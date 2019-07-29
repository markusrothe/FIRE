#ifndef FIRE_Renderer_h
#define FIRE_Renderer_h

namespace FIRE
{
class Scene;
struct Renderable;
class TextOverlay;
class Renderer
{
public:
    virtual ~Renderer() = default;
    virtual void Submit(Renderable const& renderable) = 0;
    virtual void Submit(TextOverlay overlay) = 0;
    virtual void Render(float windowWidth, float windowHeight) = 0;
    virtual void ToggleWireframe() = 0;
};
} // namespace FIRE

#endif // FIRE_Renderer_h
