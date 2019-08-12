#ifndef FIRE_OVERLAYBUILDER_h
#define FIRE_OVERLAYBUILDER_h

#include <FIRE/TextOverlay.h>
#include <cstdint>
#include <string>

namespace FIRE
{
class AssetFacade;
class OverlayBuilder
{
public:
    OverlayBuilder(AssetFacade& assets, std::string const& namePrefix, uint32_t count);

    OverlayBuilder& WithText(std::string const& text);
    OverlayBuilder& At(float x, float y);
    OverlayBuilder& ScaledBy(float scale);

    std::vector<TextOverlay> Build();

private:
    std::vector<TextOverlay> overlays;
    uint32_t textIdx{0};
    uint32_t atIdx{0};
    uint32_t scaleIdx{0};
};
} // namespace FIRE

#endif // FIRE_OVERLAYBUILDER_h
