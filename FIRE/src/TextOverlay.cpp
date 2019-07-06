#include <FIRE/TextOverlay.h>

namespace FIRE
{
TextOverlay::TextOverlay(std::string text, float x, float y)
    : m_text(text)
    , m_x(x)
    , m_y(y)
{
}

std::string TextOverlay::GetText() const
{
    return m_text;
}

float TextOverlay::x() const
{
    return m_x;
}

float TextOverlay::y() const
{
    return m_y;
}

bool operator==(TextOverlay const& lhs, TextOverlay const& rhs)
{
    return lhs.x() == rhs.x() &&
           lhs.y() == rhs.y() &&
           lhs.GetText() == rhs.GetText();
}

bool operator!=(TextOverlay const& lhs, TextOverlay const& rhs)
{
    return !(lhs == rhs);
}
} // namespace FIRE
