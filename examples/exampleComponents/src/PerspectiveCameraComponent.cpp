#include "PerspectiveCameraComponent.h"

#include <FIRE/Message.h>
#include <FIRE/SceneObject.h>
namespace examples
{

PerspectiveCameraComponent::PerspectiveCameraComponent(FIRE::SceneObject& sceneObject, float fovy, float aspect, float near, float far)
    : FIRE::CameraComponent(fovy, aspect, near, far)
{
    auto& transform = sceneObject.GetTransform();
    transform.SetPosition({0.0f, 2.0f, 10.0f});
    transform.SetLookAt({0.0f, 2.0f, 0.0f});
}

PerspectiveCameraComponent::~PerspectiveCameraComponent() = default;

void PerspectiveCameraComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene&)
{
    auto& transform = sceneObject.GetTransform();
    transform.Translate(transform.Acceleration());
}

std::optional<std::any> PerspectiveCameraComponent::Receive(FIRE::Message msg)
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
