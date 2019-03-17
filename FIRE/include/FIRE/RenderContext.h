#ifndef FIRE_RenderContext_h
#define FIRE_RenderContext_h

namespace FIRE
{
class RenderContext
{
public:
    virtual ~RenderContext() = default;
    virtual void SwapBuffers() = 0;
    virtual void PollEvents() = 0;
    virtual bool ShouldClose() = 0;
    virtual void Close() = 0;
    virtual void Resize(unsigned int width, unsigned int height) = 0;
};
} // namespace FIRE
#endif // FIRE_RenderContext_h
