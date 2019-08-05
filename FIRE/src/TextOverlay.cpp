#include <FIRE/TextOverlay.h>

#include <utility>

namespace FIRE
{
TextOverlay::TextOverlay(
    std::string name,
    std::string text,
    float x,
    float y,
    Material mat,
    float scale /*= 1.0f */)
    : name(std::move(name))
    , text(std::move(text))
    , x(x)
    , y(y)
    , scale(scale)
    , material(std::move(mat))
{
}

bool operator==(TextOverlay const& lhs, TextOverlay const& rhs)
{
    return lhs.name == rhs.name;
}

bool operator!=(TextOverlay const& lhs, TextOverlay const& rhs)
{
    return !(lhs == rhs);
}
} // namespace FIRE
