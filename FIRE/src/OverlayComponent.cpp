#include <FIRE/OverlayComponent.h>
#include <FIRE/OverlaySubmitter.h>

namespace FIRE
{
OverlayComponent::OverlayComponent(OverlaySubmitter& overlaySubmitter, std::vector<TextOverlay> overlays)
    : overlaySubmitter(overlaySubmitter)
    , overlays(std::move(overlays))
{
}

void OverlayComponent::Setup(SceneObject&)
{
}

void OverlayComponent::Update(double deltaTime, SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(deltaTime, sceneObject, scene);
    for(auto const& overlay : overlays)
    {
        overlaySubmitter.Submit(overlay);
    }
}

std::optional<std::any> OverlayComponent::Receive(Message const&, SceneObject&)
{
    return std::optional<std::any>();
}

void OverlayComponent::DoUpdate(double, SceneObject&, Scene&)
{
}
} // namespace FIRE