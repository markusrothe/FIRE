#ifndef fire_renderer_h
#define fire_renderer_h

#include <vector>

namespace Fire
{
    class Renderable;
    
    class Renderer
    {
    public:
        void Render(std::vector<Renderable*> const& renderables);
    };

} // namespace Fire

#endif // fire_renderer_h
