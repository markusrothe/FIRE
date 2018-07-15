#ifndef fire_renderingdelegate_h
#define fire_renderingdelegate_h

namespace Fire
{
class Renderable;

class RenderingDelegate
{
public:
    virtual ~RenderingDelegate() {}

    virtual void Bind(Renderable* renderable) = 0;
    virtual void Render(Renderable* renderable) = 0;
    virtual void Unbind(Renderable* renderable) = 0;
};
} // namespace Fire

#endif // fire_renderingdelegate_h
