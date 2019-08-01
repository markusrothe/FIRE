#include "FPSOverlayComponent.h"
#include <FIRE/Message.h>
#include <FIRE/Renderer.h>
#include <FIRE/TextOverlay.h>
#include <sstream>
namespace examples
{

FPSOverlayComponent::FPSOverlayComponent(FIRE::Renderer& renderer)
    : FIRE::RenderingComponent(renderer)
{
}

void FPSOverlayComponent::DoUpdate(double, FIRE::SceneObject&, FIRE::Scene&)
{
    //std::stringstream ss;
    //ss << static_cast<int>(1.0 / deltaTime);

    //m_renderer.Submit(FIRE::TextOverlay("fpsOverlay", ss.str(), 0.02f, 0.02f, mat, 0.5f));
}

std::optional<std::any> FPSOverlayComponent::Receive(FIRE::Message, FIRE::SceneObject&)
{
    return std::nullopt;
}
} // namespace examples
