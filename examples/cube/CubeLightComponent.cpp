#include "CubeLightComponent.h"
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>

namespace examples
{

void CubeLightComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene&)
{
    sceneObject.GetTransform().SetPosition({0.0f, 80.0f, 0.0f});
    m_transform = sceneObject.GetTransform();
}

std::optional<std::any> CubeLightComponent::Receive(FIRE::Message msg)
{
    if(msg.id == 2)
    {
        return m_transform.Position();
    }

    return std::nullopt;
}

} // namespace examples
