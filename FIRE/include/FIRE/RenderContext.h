#ifndef FIRE_RenderContext_h
#define FIRE_RenderContext_h

namespace FIRE
{
class RenderContext
{
public:
    virtual ~RenderContext() = default;
    virtual void SwapBuffers() = 0;
};
} // namespace FIRE
#endif // FIRE_RenderContext_h
