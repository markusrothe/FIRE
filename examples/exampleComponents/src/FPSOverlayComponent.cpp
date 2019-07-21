#include "FPSOverlayComponent.h"
#include <FIRE/Message.h>
#include <FIRE/TextOverlay.h>
#include <FIRE/TextRenderer.h>
#include <iomanip>
#include <sstream>
namespace examples
{

FPSOverlayComponent::FPSOverlayComponent(FIRE::TextRenderer& renderer)
    : FIRE::OverlayComponent(renderer)
{
}

void FPSOverlayComponent::DoUpdate(double deltaTime, FIRE::SceneObject&, FIRE::Scene&)
{
    std::stringstream ss;
    ss << static_cast<int>(1.0 / deltaTime);

    renderer.Submit(FIRE::TextOverlay(0, ss.str(), 0.02f, 0.02f, 0.5f));
}

std::optional<std::any> FPSOverlayComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}
} // namespace examples
