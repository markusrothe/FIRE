#ifndef FIRE_Message_h
#define FIRE_Message_h

#include <utility>
namespace FIRE
{

enum class MessageID
{
    GetViewMatrix = 0,
    GetProjectionMatrix = 1,
    GetLightPosition = 2
};

class Message
{
public:
    explicit Message(MessageID id)
        : id(id)
    {
    }

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

} // namespace FIRE

#endif // FIRE_Message_h