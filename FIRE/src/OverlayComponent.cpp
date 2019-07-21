#include <FIRE/OverlayComponent.h>

namespace FIRE
{
OverlayComponent::OverlayComponent(TextRenderer& renderer)
    : renderer(renderer)
{
}

OverlayComponent::~OverlayComponent() = default;

void OverlayComponent::Setup(SceneObject&)
{
}

void OverlayComponent::Update(double deltaTime, SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(deltaTime, sceneObject, scene);
}

} // namespace FIRE
