#include "PointLightComponent.h"
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>

namespace examples
{

void PointLightComponent::Setup(FIRE::SceneObject& sceneObject)
{
    sceneObject.GetTransform().SetPosition({0.0f, 5.0f, 0.0f});
}

void PointLightComponent::DoUpdate(double, FIRE::SceneObject&, FIRE::Scene&)
{
}

std::optional<std::any> PointLightComponent::Receive(FIRE::Message msg, FIRE::SceneObject& sceneObject)
{
    if(msg.id == 2)
    {
        return sceneObject.GetTransform().Position();
    }

    return std::nullopt;
}

} // namespace examples
