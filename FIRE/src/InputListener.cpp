#include "InputListener.h"
#include <FIRE/Window.h>

namespace FIRE
{
void InputListener::RegisterKeyEvent(Key key, KeyAction action, std::function<void(void)> const& callback)
{
    m_keyCallbacks.insert(std::make_pair(std::make_pair(key, action), callback));
}

void InputListener::RegisterMouseEvent(std::function<void(double, double)> mouseCallback)
{
    m_mouseCallback = std::move(mouseCallback);
}

void InputListener::UnregisterMouseEvent()
{
    m_mouseCallback = nullptr;
}

void InputListener::RegisterMouseButtonEvent(MouseKey key, KeyAction action, std::function<void(void)> const& callback)
{
    m_mouseButtonCallbacks.insert(std::make_pair(std::make_pair(key, action), callback));
}

void InputListener::KeyboardInput(Key key, KeyAction action)
{
    auto callback = m_keyCallbacks.find(std::make_pair(key, action));
    if(callback != m_keyCallbacks.end() && callback->second)
    {
        (callback->second)();
    }
}

void InputListener::MouseInput(double x, double y)
{
    if(m_mouseCallback)
    {
        m_mouseCallback(x, y);
    }
}

void InputListener::MouseKeyInput(MouseKey key, KeyAction action)
{
    auto callback = m_mouseButtonCallbacks.find(std::make_pair(key, action));
    if(callback != m_mouseButtonCallbacks.end() && callback->second)
    {
        (callback->second)();
    }
}
} // namespace FIRE
