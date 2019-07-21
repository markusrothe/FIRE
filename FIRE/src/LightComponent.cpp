#include <FIRE/LightComponent.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>

namespace FIRE
{

LightComponent::~LightComponent() = default;

void LightComponent::Setup(SceneObject&)
{
    // base implementation, do nothing
}

void LightComponent::Update(double deltaTime, SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(deltaTime, sceneObject, scene);
}

} // namespace FIRE
