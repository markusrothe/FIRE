#ifndef FIRE_Message_h
#define FIRE_Message_h

#include <FIRE/Key.h>
#include <FIRE/KeyAction.h>
#include <FIRE/MouseKey.h>
#include <functional>
#include <utility>
namespace FIRE
{
class Transform;

enum class MessageID
{
    GetViewMatrix = 0,
    GetProjectionMatrix = 1,
    GetLightPosition = 2,
    RegisterKeyEvent = 3,
    UnregisterKeyEvent = 4,
    RegisterMouseMoveEvent = 5,
    UnregisterMouseMoveEvent = 6,
    RegisterMouseButtonEvent = 7,
    UnregisterMouseButtonEvent = 8

};

class Message
{
public:
    explicit Message(MessageID id)
        : id(id)
    {
    }

    virtual ~Message() = default;

    bool operator<(Message const& rhs) const
    {
        return id < rhs.id;
    }

    bool operator>(Message const& rhs) const
    {
        return rhs < *this;
    }

    bool operator<=(Message const& rhs) const
    {
        return !(rhs < *this);
    }

    bool operator>=(Message const& rhs) const
    {
        return !(*this < rhs);
    }

    MessageID id;
};

inline bool operator==(Message const& lhs, Message const& rhs)
{
    return lhs.id == rhs.id;
}

inline bool operator!=(Message const& lhs, Message const& rhs)
{
    return !(lhs == rhs);
}

class KeyRegisterMessage : public Message
{
public:
    explicit KeyRegisterMessage(MessageID id, Key key, KeyAction action, std::function<void(Transform&)> callback)
        : Message(id)
        , key(key)
        , action(action)
        , callback(std::move(callback))
    {
    }

    Key key;
    KeyAction action;
    std::function<void(Transform&)> callback;
};

class MouseKeyRegisterMessage : public Message
{
public:
    explicit MouseKeyRegisterMessage(MessageID id, MouseKey key, KeyAction action, std::function<void(Transform&)> callback)
        : Message(id)
        , key(key)
        , action(action)
        , callback(std::move(callback))
    {
    }

    MouseKey key;
    KeyAction action;
    std::function<void(Transform&)> callback;
};

class MouseMoveRegisterMessage : public Message
{
public:
    explicit MouseMoveRegisterMessage(MessageID id, std::function<void(double, double)> callback)
        : Message(id)
        , callback(std::move(callback))
    {
    }
    std::function<void(double, double)> callback;
};

} // namespace FIRE

#endif // FIRE_Message_h