#include "CubeOverlayComponent.h"
#include <FIRE/Message.h>
#include <FIRE/TextOverlay.h>
#include <FIRE/TextRenderer.h>
#include <sstream>
namespace examples
{

CubeOverlayComponent::CubeOverlayComponent(FIRE::TextRenderer& renderer)
    : FIRE::OverlayComponent(renderer)
{
}

void CubeOverlayComponent::DoUpdate(double deltaTime, FIRE::SceneObject&, FIRE::Scene&)
{
    std::stringstream ss;
    ss << (1.0 / deltaTime);
    renderer.Submit(FIRE::TextOverlay(0, ss.str(), 0.02f, 0.02f, 0.5f));
}

std::optional<std::any> CubeOverlayComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}
} // namespace examples
