#include "root.h"

namespace Fire
{
    Root::Root(std::string_view const& windowName
               , unsigned int windowWidth
               , unsigned int windowHeight)
        : m_windowName(windowName)
        , m_windowWidth(windowWidth)
        , m_windowHeight(windowHeight)
    {

    }
} // namespace Fire
