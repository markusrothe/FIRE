#include "window.h"
#include "keyhandler.h"

namespace blocks
{
    namespace
    {
        // glfw is a pure C-API, so a free function is needed.
        // The window object can be passed via glfwGetWindowUserPointer() into the free function
        void KeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
        {
            Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
            window->KeyPressed(key, action);
        }
    }

    Window::Window(unsigned int width, unsigned int height, std::string const name, KeyHandler& keyHandler)
        : m_window(nullptr)
        , m_keyHandler(keyHandler)
    {
        glfwInit();
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        m_window = glfwCreateWindow(width, height, "Blocks", NULL, NULL);
        glfwSetWindowUserPointer(m_window, this);

        glfwMakeContextCurrent(m_window);

        glfwSetKeyCallback(m_window, KeyCallback);
    }

    void Window::KeyPressed(int key, int action)
    {
        m_keyHandler.KeyPressed(key, action);
    }

    bool Window::WindowShouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    void Window::PollEvents() const
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers() const
    {
        glfwSwapBuffers(m_window);
    }
}