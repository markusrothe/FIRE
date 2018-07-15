#ifndef fire_rendercontext_h
#define fire_rendercontext_h

namespace Fire
{
class RenderContext
{
public:
    virtual ~RenderContext() {}

    virtual void PollEvents() = 0;

    virtual void SwapBuffers() = 0;

    virtual bool ShouldClose() = 0;
};
} // namespace Fire

#endif // fire_rendercontext_h
