#ifndef fire_rendercontext_h
#define fire_rendercontext_h

namespace Fire
{
    class RenderContext
    {
    public:
        virtual ~RenderContext() {}
        virtual void InitializeContext() = 0;

        virtual void SetWindowHints() = 0;

        virtual void PollEvents() = 0;
        
        virtual void SwapBuffers() = 0;
    };
}

#endif // fire_rendercontext_h
