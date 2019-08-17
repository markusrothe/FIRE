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

std::optional<std::any> LightComponent::Receive(Message msg, SceneObject& sceneObject)
{
    if(msg.id == FIRE::MessageID::GetLightPosition)
    {
        return sceneObject.GetTransform().Position();
    }

    return std::optional<std::any>();
}
void LightComponent::DoUpdate(double, SceneObject&, Scene&)
{
    // base implementation, Do nothing.
}

} // namespace FIRE
