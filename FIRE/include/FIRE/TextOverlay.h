#ifndef FIRE_TextOverlay_h
#define FIRE_TextOverlay_h

#include <string>
namespace FIRE
{
class TextOverlay
{
public:
    TextOverlay(std::string text, float x, float y);

    std::string GetText() const;
    float x() const;
    float y() const;

private:
    std::string m_text;
    float m_x;
    float m_y;
};

bool operator==(TextOverlay const& lhs, TextOverlay const& rhs);
bool operator!=(TextOverlay const& lhs, TextOverlay const& rhs);
} // namespace FIRE

#endif // FIRE_TextOverlay_h