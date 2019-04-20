#ifndef FIRE_Renderer_h
#define FIRE_Renderer_h

namespace FIRE
{
class Scene;
class Renderer
{
public:
    virtual ~Renderer() = default;
    virtual void Render(Scene const&) = 0;
};
} // namespace FIRE

#endif // FIRE_Renderer_h
