#ifndef FIRE_Renderer_h
#define FIRE_Renderer_h

namespace FIRE
{
class Scene;
struct Renderable;
class Renderer
{
public:
    virtual ~Renderer() = default;
    virtual void Submit(Renderable const& renderable) = 0;
    virtual void Render(Scene const& scene, float windowWidth, float windowHeight) = 0;
};
} // namespace FIRE

#endif // FIRE_Renderer_h
