#include "glRenderContext.h"

namespace Fire
{
GLRenderContext::GLRenderContext(
    std::string const& name, unsigned int width, unsigned int height)
    : m_window(nullptr)
{
    glfwInit();

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_window);

    glewInit();
}

void GLRenderContext::PollEvents() { glfwPollEvents(); }

void GLRenderContext::SwapBuffers() { glfwSwapBuffers(m_window); }

bool GLRenderContext::ShouldClose() { return glfwWindowShouldClose(m_window); }

} // namespace Fire
