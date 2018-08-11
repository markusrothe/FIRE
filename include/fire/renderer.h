#ifndef fire_renderer_h
#define fire_renderer_h

#include <memory>
#include <vector>

namespace Fire
{
class Renderable;
class RenderingDelegate;

class Renderer
{
public:
    explicit Renderer(std::unique_ptr<RenderingDelegate> renderingDelegate);

    ~Renderer();

    void Render(std::vector<Renderable*> const& renderables);

private:
    std::unique_ptr<RenderingDelegate> const m_renderingDelegate;
};

} // namespace Fire

#endif // fire_renderer_h
