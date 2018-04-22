#include "keyhandler.h"
#include <GLFW/glfw3.h>
#include <algorithm>

namespace blocks
{
    void KeyHandler::AddListener(KeyHandlerListener* listener)
    {
        m_listeners.push_back(listener);
    }

    void KeyHandler::KeyPressed(int key, int action)
    {
        std::for_each(std::begin(m_listeners), std::end(m_listeners), [&](KeyHandlerListener* listener)
        { 
            listener->Notify(key, action); 
        });
    }
}
