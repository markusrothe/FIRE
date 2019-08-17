#include <FIRE/RenderContext.h>
#include <FIRE/Window.h>
#include <cassert>
namespace FIRE
{
Window::Window(std::string const& title, unsigned int width, unsigned int height)
    : m_title(title)
    , m_width(width)
    , m_height(height)
{
}

Window::~Window() = default;

std::string Window::GetTitle() const
{
    return m_title;
}

unsigned int Window::GetWidth() const
{
    return m_width;
}

unsigned int Window::GetHeight() const
{
    return m_height;
}

void Window::Resize(unsigned int newWidth, unsigned int newHeight)
{
    m_width = newWidth;
    m_height = newHeight;

    assert(m_context);
    m_context->Resize(m_width, m_height);
}

bool Window::ShouldClose() const
{
    assert(m_context);
    return m_context->ShouldClose();
}

void Window::Close()
{
    assert(m_context);
    m_context->Close();
}

void Window::SetRenderContext(std::unique_ptr<RenderContext> context)
{
    m_context = std::move(context);
}

void Window::SetInputListener(std::shared_ptr<InputListener> inputListener)
{
    assert(m_context);
    m_inputListener = std::move(inputListener);
    m_context->RegisterInputListener(m_inputListener.get());
}

void Window::SwapBuffers()
{
    assert(m_context);
    m_context->SwapBuffers();
}

void Window::PollEvents()
{
    assert(m_context);
    m_context->PollEvents();
}

void Window::CaptureCursor()
{
    assert(m_context);
    m_context->CaptureCursor();
}

void Window::ReleaseCursor()
{
    assert(m_context);
    m_context->ReleaseCursor();
}

} // namespace FIRE
