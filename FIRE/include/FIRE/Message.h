#ifndef FIRE_Message_h
#define FIRE_Message_h

#include <utility>
namespace FIRE
{

class Message
{
public:
    explicit Message(int id)
        : id(std::move(id))
    {
    }

    int id;
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