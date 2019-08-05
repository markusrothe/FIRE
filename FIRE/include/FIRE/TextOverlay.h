#ifndef FIRE_TextOverlay_h
#define FIRE_TextOverlay_h

#include <FIRE/Material.h>
#include <string>
namespace FIRE
{
class TextOverlay
{
public:
    TextOverlay() = default;

    TextOverlay(
        std::string name,
        std::string text,
        float x,
        float y,
        Material mat,
        float scale = 1.0f);

    std::string name;
    std::string text;
    float x;
    float y;
    float scale;
    Material material;
};

bool operator==(TextOverlay const& lhs, TextOverlay const& rhs);
bool operator!=(TextOverlay const& lhs, TextOverlay const& rhs);
} // namespace FIRE

#endif // FIRE_TextOverlay_h