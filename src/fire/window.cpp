#include "window.h"
#include "glRenderContext.h"

namespace Fire
{
Window::Window(
    std::string const& windowName, unsigned int windowWidth,
    unsigned int windowHeight, std::unique_ptr<RenderContext>&& renderContext)
    : m_windowName(windowName)
    , m_windowWidth(windowWidth)
    , m_windowHeight(windowHeight)
    , m_renderContext(std::move(renderContext))
{
}

Window::~Window() {}

std::string Window::GetName() const { return m_windowName; }

unsigned int Window::GetWidth() const { return m_windowWidth; }

unsigned int Window::GetHeight() const { return m_windowHeight; }

RenderContext* Window::GetRenderContext() const
{
    return m_renderContext.get();
}

void Window::SwapBuffers() { m_renderContext->SwapBuffers(); }

void Window::PollEvents() { m_renderContext->PollEvents(); }

bool Window::ShouldClose() { return m_renderContext->ShouldClose(); }

} // namespace Fire
