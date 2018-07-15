#ifndef fire_renderer_h
#define fire_renderer_h

#include <memory>
#include <vector>

namespace Fire
{
class Renderable;
class RenderingDelegate;
class Binder;

class Renderer
{
public:
    Renderer(
        std::unique_ptr<RenderingDelegate>&& renderingDelegate,
        std::unique_ptr<Binder>&& textureBinder,
        std::unique_ptr<Binder>&& materialBinder);

    ~Renderer();

    void Render(std::vector<Renderable*> const& renderables);

private:
    std::unique_ptr<RenderingDelegate> const m_renderingDelegate;
    std::unique_ptr<Binder> const m_textureBinder;
    std::unique_ptr<Binder> const m_materialBinder;
};

} // namespace Fire

#endif // fire_renderer_h
