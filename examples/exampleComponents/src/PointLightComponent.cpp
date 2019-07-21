#include "PointLightComponent.h"
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>

namespace examples
{

void PointLightComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene&)
{
    sceneObject.GetTransform().SetPosition({130.0f, 2000.0f, 15.0f});
    m_transform = sceneObject.GetTransform();
}

std::optional<std::any> PointLightComponent::Receive(FIRE::Message msg)
{
    if(msg.id == 2)
    {
        return m_transform.Position();
    }

    return std::nullopt;
}

} // namespace examples
