#include "windowFactory.h"
#include "glRenderContext.h"
#include "window.h"

namespace Fire
{
namespace WindowFactory
{

std::unique_ptr<Window> CreateGLWindow(
    std::string const& windowName, unsigned int windowWidth,
    unsigned int windowHeight)
{
    auto renderContext = std::make_unique<GLRenderContext>(
        windowName, windowWidth, windowHeight);
    return std::make_unique<Window>(
        windowName, windowWidth, windowHeight, std::move(renderContext));
}

} // namespace WindowFactory
} // namespace Fire
