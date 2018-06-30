#ifndef fire_renderingdelegate_h
#define fire_renderingdelegate_h

namespace Fire
{
    class Renderable;
    
    class RenderingDelegate
    {
    public:
        virtual ~RenderingDelegate() {}
	
        virtual void Render(Fire::Renderable* renderable) = 0;
    };
} // namespace Fire

#endif // fire_renderingdelegate_h
