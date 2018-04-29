#ifndef fire_windowfactory_h
#define fire_windowfactory_h

#include <string>
#include <memory>

namespace Fire
{
    class Window;
    
    namespace WindowFactory
    {
        std::unique_ptr<Window> CreateGLWindow(std::string const& windowName,
                                               unsigned int windowWidth,
                                               unsigned int windowHeight);                
    } // namespace WindowFactoryx   
} // namespace Fire

#endif // fire_windowfactory_h
