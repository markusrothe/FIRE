#include <FIRE/RenderContext.h>
#include <FIRE/Window.h>
#include <cassert>
namespace FIRE
{
Window::Window(std::string const title, unsigned int width, unsigned int height)
    : m_title(title)
    , m_width(width)
    , m_height(height)
{
}

Window::~Window() = default;

std::string Window::GetTitle() const { return m_title; }
unsigned int Window::GetWidth() const { return m_width; }
unsigned int Window::GetHeight() const { return m_height; }
void Window::Resize(unsigned int newWidth, unsigned int newHeight)
{
    m_width = newWidth;
    m_height = newHeight;
}

bool Window::ShouldClose() const { return m_shouldClose; }
void Window::Close() { m_shouldClose = true; }

void Window::SetRenderContext(std::unique_ptr<RenderContext> context)
{
    m_context = std::move(context);
}
void Window::SwapBuffers()
{
    assert(nullptr != m_context);
    m_context->SwapBuffers();
}
} // namespace FIRE
