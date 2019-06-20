#include "GLRenderContext.h"
#include <FIRE/InputListener.h>
#include <FIRE/Key.h>
#include <FIRE/KeyAction.h>
#include <FIRE/Window.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>

namespace FIRE
{
FIRE::KeyAction ToFIREKeyAction(int action)
{
    switch(action)
    {
    case GLFW_PRESS:
        return FIRE::KeyAction::PRESS;
    case GLFW_REPEAT:
        return FIRE::KeyAction::REPEAT;
    case GLFW_RELEASE:
        return FIRE::KeyAction::RELEASE;
    default:
        assert(false);
        return FIRE::KeyAction::INVALID;
    };
}

FIRE::MouseKey ToFIREMouseKey(int key)
{
    switch(key)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        return FIRE::MouseKey::LEFT_BUTTON;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        return FIRE::MouseKey::MIDDLE_BUTTON;
    case GLFW_MOUSE_BUTTON_RIGHT:
        return FIRE::MouseKey::RIGHT_BUTTON;
    default:
        assert(false);
        return FIRE::MouseKey::INVALID;
    }
}

FIRE::Key ToFIREKey(int key)
{
    switch(key)
    {
    case GLFW_KEY_A:
        return FIRE::Key::KEY_A;
    case GLFW_KEY_B:
        return FIRE::Key::KEY_B;
    case GLFW_KEY_C:
        return FIRE::Key::KEY_C;
    case GLFW_KEY_D:
        return FIRE::Key::KEY_D;
    case GLFW_KEY_E:
        return FIRE::Key::KEY_E;
    case GLFW_KEY_F:
        return FIRE::Key::KEY_F;
    case GLFW_KEY_G:
        return FIRE::Key::KEY_G;
    case GLFW_KEY_H:
        return FIRE::Key::KEY_H;
    case GLFW_KEY_I:
        return FIRE::Key::KEY_I;
    case GLFW_KEY_J:
        return FIRE::Key::KEY_J;
    case GLFW_KEY_K:
        return FIRE::Key::KEY_K;
    case GLFW_KEY_L:
        return FIRE::Key::KEY_L;
    case GLFW_KEY_M:
        return FIRE::Key::KEY_M;
    case GLFW_KEY_N:
        return FIRE::Key::KEY_N;
    case GLFW_KEY_O:
        return FIRE::Key::KEY_O;
    case GLFW_KEY_P:
        return FIRE::Key::KEY_P;
    case GLFW_KEY_Q:
        return FIRE::Key::KEY_Q;
    case GLFW_KEY_R:
        return FIRE::Key::KEY_R;
    case GLFW_KEY_S:
        return FIRE::Key::KEY_S;
    case GLFW_KEY_T:
        return FIRE::Key::KEY_T;
    case GLFW_KEY_U:
        return FIRE::Key::KEY_U;
    case GLFW_KEY_V:
        return FIRE::Key::KEY_V;
    case GLFW_KEY_W:
        return FIRE::Key::KEY_W;
    case GLFW_KEY_X:
        return FIRE::Key::KEY_X;
    case GLFW_KEY_Y:
        return FIRE::Key::KEY_Y;
    case GLFW_KEY_Z:
        return FIRE::Key::KEY_Z;
    case GLFW_KEY_0:
        return FIRE::Key::KEY_0;
    case GLFW_KEY_1:
        return FIRE::Key::KEY_1;
    case GLFW_KEY_2:
        return FIRE::Key::KEY_2;
    case GLFW_KEY_3:
        return FIRE::Key::KEY_3;
    case GLFW_KEY_4:
        return FIRE::Key::KEY_4;
    case GLFW_KEY_5:
        return FIRE::Key::KEY_5;
    case GLFW_KEY_6:
        return FIRE::Key::KEY_6;
    case GLFW_KEY_7:
        return FIRE::Key::KEY_7;
    case GLFW_KEY_8:
        return FIRE::Key::KEY_8;
    case GLFW_KEY_9:
        return FIRE::Key::KEY_9;
    case GLFW_KEY_ESCAPE:
        return FIRE::Key::KEY_ESC;
    default:
        assert(false);
        return FIRE::Key::INVALID;
    }
}

static void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    void* windowUserPointer = glfwGetWindowUserPointer(window);
    assert(windowUserPointer);

    InputListener* inputListener = reinterpret_cast<InputListener*>(windowUserPointer);
    inputListener->KeyboardInput(ToFIREKey(key), ToFIREKeyAction(action));
}

static void mouse_callback(GLFWwindow* window, double x, double y)
{
    void* windowUserPointer = glfwGetWindowUserPointer(window);
    assert(windowUserPointer);

    InputListener* inputListener = reinterpret_cast<InputListener*>(windowUserPointer);
    inputListener->MouseInput(x, y);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int /*mods*/)
{
    void* windowUserPointer = glfwGetWindowUserPointer(window);
    assert(windowUserPointer);

    InputListener* inputListener = reinterpret_cast<InputListener*>(windowUserPointer);
    inputListener->MouseKeyInput(ToFIREMouseKey(button), ToFIREKeyAction(action));
}

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

    void RegisterInputListener(InputListener* inputListener);

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

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    m_window = glfwCreateWindow(
        window.GetWidth(), window.GetHeight(), window.GetTitle().c_str(), NULL,
        NULL);

    if(!m_window)
    {
        std::cerr << "glfwCreateWindow failed\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetKeyCallback(m_window, key_callback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(m_window, mouse_callback);

    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
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

void GLRenderContext::Impl::RegisterInputListener(InputListener* inputListener)
{
    glfwSetWindowUserPointer(m_window, reinterpret_cast<void*>(inputListener));
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

void GLRenderContext::RegisterInputListener(InputListener* inputListener)
{
    m_impl->RegisterInputListener(inputListener);
}

} // namespace FIRE
