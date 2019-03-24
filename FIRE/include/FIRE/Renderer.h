#ifndef FIRE_Renderer_h
#define FIRE_Renderer_h

namespace FIRE
{
class Renderable;
class Renderer
{
public:
    virtual ~Renderer() = default;
    virtual void Render(Renderable const&) = 0;
};
} // namespace FIRE

#endif // FIRE_Renderer_h
