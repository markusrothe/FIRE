#ifndef FIRE_TextOverlay_h
#define FIRE_TextOverlay_h

#include <string>
namespace FIRE
{
class TextOverlay
{
public:
    TextOverlay(std::string text, float x, float y, float scale = 1.0f);

    std::string text;
    float x;
    float y;
    float scale;
};

bool operator==(TextOverlay const& lhs, TextOverlay const& rhs);
bool operator!=(TextOverlay const& lhs, TextOverlay const& rhs);
} // namespace FIRE

#endif // FIRE_TextOverlay_h