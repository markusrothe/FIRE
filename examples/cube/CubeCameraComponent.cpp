#include "CubeCameraComponent.h"

#include <FIRE/Message.h>
#include <FIRE/SceneObject.h>
namespace examples
{

CubeCameraComponent::CubeCameraComponent(FIRE::SceneObject& sceneObject, float fovy, float aspect, float near, float far)
    : FIRE::CameraComponent(fovy, aspect, near, far)
{
    auto& transform = sceneObject.GetTransform();
    transform.SetPosition({0.0f, 2.0f, 10.0f});
    transform.SetLookAt({0.0f, 2.0f, 0.0f});
}

CubeCameraComponent::~CubeCameraComponent() = default;

void CubeCameraComponent::DoUpdate(double, FIRE::SceneObject&, FIRE::Scene&)
{
}

std::optional<std::any> CubeCameraComponent::Receive(FIRE::Message msg)
{
    if(msg.id == 0)
    {
        return GetViewMatrix();
    }
    else if(msg.id == 1)
    {
        return GetProjectionMatrix();
    }

    return std::nullopt;
}
} // namespace examples
