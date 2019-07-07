#include <FIRE/TextOverlay.h>

namespace FIRE
{
TextOverlay::TextOverlay(std::string text, float x, float y, float scale /*= 1.0f */)
    : text(text)
    , x(x)
    , y(y)
    , scale(scale)
{
}

bool operator==(TextOverlay const& lhs, TextOverlay const& rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.scale == rhs.scale &&
           lhs.text == rhs.text;
}

bool operator!=(TextOverlay const& lhs, TextOverlay const& rhs)
{
    return !(lhs == rhs);
}
} // namespace FIRE
