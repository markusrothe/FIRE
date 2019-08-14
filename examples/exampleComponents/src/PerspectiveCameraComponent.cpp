#include "PerspectiveCameraComponent.h"

#include <FIRE/Message.h>
#include <FIRE/SceneObject.h>
namespace examples
{

PerspectiveCameraComponent::PerspectiveCameraComponent(float fovy, float aspect, float near, float far)
    : FIRE::CameraComponent(fovy, aspect, near, far)
{
}

PerspectiveCameraComponent::~PerspectiveCameraComponent() = default;

void PerspectiveCameraComponent::Setup(FIRE::SceneObject&)
{
}

void PerspectiveCameraComponent::DoUpdate(double, FIRE::SceneObject& sceneObject, FIRE::Scene&)
{
    auto& transform = sceneObject.GetTransform();
    transform.Translate(transform.Acceleration());
}

std::optional<std::any> PerspectiveCameraComponent::Receive(FIRE::Message msg, FIRE::SceneObject&)
{
    if(msg.id == FIRE::MessageID::GetViewMatrix)
    {
        return GetViewMatrix();
    }
    else if(msg.id == FIRE::MessageID::GetProjectionMatrix)
    {
        return GetProjectionMatrix();
    }

    return std::nullopt;
}
} // namespace examples
