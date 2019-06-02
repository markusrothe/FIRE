#ifndef FIRE_InputListener_h
#define FIRE_InputListener_h

#include <FIRE/Key.h>
#include <FIRE/KeyAction.h>
#include <functional>
#include <type_traits>
#include <unordered_map>

namespace std
{
template <>
class hash<std::pair<FIRE::Key, FIRE::KeyAction>>
{
public:
    size_t operator()(pair<FIRE::Key, FIRE::KeyAction> const& val) const
    {
        auto key = static_cast<underlying_type_t<FIRE::Key>>(val.first);
        auto action = static_cast<underlying_type_t<FIRE::KeyAction>>(val.second);

        hash<underlying_type_t<FIRE::Key>> keyHash;
        hash<underlying_type_t<FIRE::KeyAction>> actionHash;

        return keyHash(key) ^ actionHash(action);
    }
};
} // namespace std

namespace FIRE
{
class Window;
class InputListener
{
public:
    void Register(Key key, KeyAction action, std::function<void(void)> callback);
    void Call(Key key, KeyAction action);

private:
    std::unordered_map<std::pair<Key, KeyAction>, std::function<void(void)>> m_callbacks;
};
} // namespace FIRE

#endif // !FIRE_InputListener_h