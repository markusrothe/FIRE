#include <FIRE/GLRenderContext.h>
#include <FIRE/Window.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace FIRE
{

class GLRenderContext::Impl
{
public:
    explicit Impl(Window& window);

    ~Impl();

    void SwapBuffers();

private:
    GLFWwindow* m_window;
};

GLRenderContext::Impl::Impl(Window& window)
{
    if(!glfwInit())
    {
        std::cerr << "glfwInit failed\n";
        std::exit(EXIT_FAILURE);
    }

    m_window = glfwCreateWindow(
        window.GetWidth(), window.GetHeight(), window.GetTitle().c_str(), NULL,
        NULL);

    if(!m_window)
    {
        std::cerr << "glfwCreateWindow failed\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
}

GLRenderContext::Impl::~Impl() { glfwDestroyWindow(m_window); }

void GLRenderContext::Impl::SwapBuffers() { glfwSwapBuffers(m_window); }

GLRenderContext::GLRenderContext(Window& window)
    : m_impl(std::make_unique<GLRenderContext::Impl>(window))
{
}

GLRenderContext::~GLRenderContext() = default;

void GLRenderContext::SwapBuffers() { m_impl->SwapBuffers(); }

} // namespace FIRE
