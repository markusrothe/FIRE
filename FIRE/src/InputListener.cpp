#include <FIRE/InputListener.h>
#include <FIRE/Window.h>

namespace FIRE
{
void InputListener::Register(Key key, KeyAction action, std::function<void(void)> callback)
{
    m_callbacks.insert(std::make_pair(std::make_pair(key, action), callback));
}

void InputListener::Register(std::function<void(double x, double y)> mouseCallback)
{
    m_mouseCallback = std::move(mouseCallback);
}

void InputListener::KeyboardInput(Key key, KeyAction action)
{
    auto callback = m_callbacks.find(std::make_pair(key, action));
    if(callback != m_callbacks.end() && callback->second)
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
} // namespace FIRE