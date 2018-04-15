#ifndef fire_root_h
#define fire_root_h

#include <string>

namespace Fire
{
    class Root
    {
    public:
        Root(std::string const& windowName, unsigned int windowWidth, unsigned int windowHeight);
              
    private:
        std::string const m_windowName;
        unsigned int m_windowWidth;
        unsigned int m_windowHeight;
    };
}

#endif // fire_root_h
