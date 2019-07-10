#include <FIRE/TextOverlay.h>

namespace FIRE
{
TextOverlay::TextOverlay(int id, std::string text, float x, float y, float scale /*= 1.0f */)
    : id(id)
    , text(text)
    , x(x)
    , y(y)
    , scale(scale)
{
}

bool operator==(TextOverlay const& lhs, TextOverlay const& rhs)
{
    return lhs.id == rhs.id;
}

bool operator!=(TextOverlay const& lhs, TextOverlay const& rhs)
{
    return !(lhs == rhs);
}
} // namespace FIRE
