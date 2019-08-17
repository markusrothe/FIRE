#ifndef FIRE_InputListener_h
#define FIRE_InputListener_h

#include <FIRE/Key.h>
#include <FIRE/KeyAction.h>
#include <FIRE/MouseKey.h>
#include <functional>
#include <type_traits>
#include <unordered_map>

namespace std
{
template <typename KeyType>
struct hash<std::pair<KeyType, FIRE::KeyAction>>
{
public:
    size_t operator()(pair<KeyType, FIRE::KeyAction> const& val) const
    {
        auto key = static_cast<underlying_type_t<KeyType>>(val.first);
        auto action = static_cast<underlying_type_t<FIRE::KeyAction>>(val.second);

        hash<underlying_type_t<KeyType>> keyHash;
        hash<underlying_type_t<FIRE::KeyAction>> actionHash;

        return keyHash(key) ^ actionHash(action);
    }
};

} // namespace std

namespace FIRE
{
class InputListener
{
public:
    void RegisterKeyEvent(Key key, KeyAction action, std::function<void(void)> callback);
    void RegisterMouseEvent(std::function<void(double, double)> callback);
    void UnregisterMouseEvent();

    void RegisterMouseButtonEvent(MouseKey key, KeyAction action, std::function<void(void)> callback);

    void KeyboardInput(Key key, KeyAction action);
    void MouseInput(double x, double y);
    void MouseKeyInput(MouseKey key, KeyAction action);

private:
    std::unordered_map<std::pair<Key, KeyAction>, std::function<void(void)>> m_keyCallbacks;
    std::unordered_map<std::pair<MouseKey, KeyAction>, std::function<void(void)>> m_mouseButtonCallbacks;
    std::function<void(double, double)> m_mouseCallback;
};
} // namespace FIRE

#endif // !FIRE_InputListener_h
