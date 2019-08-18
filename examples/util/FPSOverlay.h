#ifndef FIRE_FPSOVERLAY_H
#define FIRE_FPSOVERLAY_H

#include <FIRE/OverlayComponent.h>
#include <algorithm>
#include <sstream>
namespace util
{
class FPSOverlay : public FIRE::OverlayComponent
{
public:
    FPSOverlay(FIRE::OverlaySubmitter& overlaySubmitter, std::vector<FIRE::TextOverlay> overlays)
        : FIRE::OverlayComponent(overlaySubmitter, std::move(overlays))
    {
    }

private:
    void DoUpdate(double deltaTime, FIRE::SceneObject&, FIRE::Scene&) override
    {
        if(auto it = std::find_if(std::begin(overlays), std::end(overlays), [](auto const& overlay) { return overlay.name == "textoverlay0"; }); it != std::cend(overlays))
        {
            std::stringstream ss;
            ss << static_cast<int>(1.0 / deltaTime);
            it->text = ss.str();
        }
    }
};
} // namespace util

#endif //FIRE_FPSOVERLAY_H
