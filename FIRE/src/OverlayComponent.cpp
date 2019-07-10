#include <FIRE/OverlayComponent.h>

namespace FIRE
{
OverlayComponent::OverlayComponent(TextRenderer& renderer)
    : renderer(renderer)
{
}

OverlayComponent::~OverlayComponent() = default;

void OverlayComponent::Update(SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(sceneObject, scene);
}

} // namespace FIRE
