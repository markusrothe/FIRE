#ifndef fire_glrendercontext_h
#define fire_glrendercontext_h

#include "renderContext.h"

namespace Fire
{
    class GLRenderContext : public RenderContext
    {
    public:
        GLRenderContext();

        virtual ~GLRenderContext(){}
        virtual void InitializeContext() override;

        virtual void SetWindowHints() override;

        virtual void PollEvents() override;
        
        virtual void SwapBuffers() override;       
    };
}

#endif // fire_glrendercontext_h
