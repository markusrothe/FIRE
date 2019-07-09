#include <FIRE/LightComponent.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>

namespace FIRE
{

LightComponent::~LightComponent() = default;

void LightComponent::Update(SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(sceneObject, scene);
}

} // namespace FIRE
