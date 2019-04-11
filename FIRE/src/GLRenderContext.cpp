#include "GLRenderContext.h"
#include <FIRE/Window.h>

#include <glad/glad.h>

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
    void PollEvents();
    bool ShouldClose();
    void Close();
    void Resize(unsigned int width, unsigned int height);

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

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

GLRenderContext::Impl::~Impl()
{
    glfwDestroyWindow(m_window);
}

void GLRenderContext::Impl::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

void GLRenderContext::Impl::PollEvents()
{
    glfwPollEvents();
}

bool GLRenderContext::Impl::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void GLRenderContext::Impl::Close()
{
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void GLRenderContext::Impl::Resize(unsigned int width, unsigned int height)
{
    glfwSetWindowSize(m_window, width, height);
}

GLRenderContext::GLRenderContext(Window& window)
    : m_impl(std::make_unique<GLRenderContext::Impl>(window))
{
}

GLRenderContext::~GLRenderContext() = default;

void GLRenderContext::SwapBuffers()
{
    m_impl->SwapBuffers();
}

void GLRenderContext::PollEvents()
{
    m_impl->PollEvents();
}

bool GLRenderContext::ShouldClose()
{
    return m_impl->ShouldClose();
}

void GLRenderContext::Close()
{
    m_impl->Close();
}

void GLRenderContext::Resize(unsigned int width, unsigned int height)
{
    m_impl->Resize(width, height);
}

} // namespace FIRE
