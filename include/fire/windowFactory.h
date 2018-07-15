#ifndef fire_windowfactory_h
#define fire_windowfactory_h

#include <memory>
#include <string>

namespace Fire
{
class Window;

namespace WindowFactory
{
std::unique_ptr<Window> CreateGLWindow(
    std::string const& windowName, unsigned int windowWidth,
    unsigned int windowHeight);
} // namespace WindowFactory
} // namespace Fire

#endif // fire_windowfactory_h
