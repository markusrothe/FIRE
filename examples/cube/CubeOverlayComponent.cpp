#include "CubeOverlayComponent.h"
#include <FIRE/Message.h>
#include <FIRE/TextOverlay.h>
#include <FIRE/TextRenderer.h>
#include <chrono>
#include <sstream>
namespace examples
{

CubeOverlayComponent::CubeOverlayComponent(FIRE::TextRenderer& renderer)
    : FIRE::OverlayComponent(renderer)
{
}

void CubeOverlayComponent::DoUpdate(FIRE::SceneObject&, FIRE::Scene&)
{
    static std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    static std::chrono::system_clock::time_point lastTime = std::chrono::system_clock::now();

    currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> timeDiff = currentTime - lastTime;
    lastTime = currentTime;

    std::stringstream ss;
    ss << (1.0 / timeDiff.count());
    renderer.Submit(FIRE::TextOverlay(ss.str(), 0.02f, 0.02f, 0.5f));
}

std::optional<std::any> CubeOverlayComponent::Receive(FIRE::Message)
{
    return std::nullopt;
}
} // namespace examples
