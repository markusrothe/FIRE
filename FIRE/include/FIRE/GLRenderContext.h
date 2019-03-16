#ifndef FIRE_GLRenderContext_h
#define FIRE_GLRenderContext_h

#include <FIRE/RenderContext.h>
#include <memory>

namespace FIRE
{

class Window;

class GLRenderContext : public RenderContext
{
public:
    explicit GLRenderContext(Window& window);
    ~GLRenderContext() override;

    GLRenderContext(GLRenderContext const&) = delete;
    GLRenderContext(GLRenderContext&&) = delete;
    GLRenderContext& operator=(GLRenderContext const&) = delete;
    GLRenderContext& operator=(GLRenderContext&&) = delete;

    void SwapBuffers() override;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
} // namespace FIRE

#endif // FIRE_GLRenderContext_h
