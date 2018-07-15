#ifndef fire_glrendercontext_h
#define fire_glrendercontext_h

#include "renderContext.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Fire
{
class GLRenderContext : public RenderContext
{
public:
    GLRenderContext(
        std::string const& name, unsigned int width, unsigned int height);

    virtual ~GLRenderContext() {}

    virtual void PollEvents() override;

    virtual void SwapBuffers() override;

    virtual bool ShouldClose() override;

private:
    GLFWwindow* m_window;
};
} // namespace Fire

#endif // fire_glrendercontext_h
