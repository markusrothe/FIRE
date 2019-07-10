#include "CubeLightComponent.h"
#include <FIRE/Message.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>

namespace examples
{

void CubeLightComponent::DoUpdate(FIRE::SceneObject& sceneObject, FIRE::Scene&)
{
    sceneObject.GetTransform().SetPosition({7.0f, 8.0f, 2.0f});
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
