#include "CubeCameraComponent.h"

#include <FIRE/SceneObject.h>
namespace examples
{

CubeCameraComponent::CubeCameraComponent(float fovy, float aspect, float near, float far)
    : FIRE::CameraComponent(fovy, aspect, near, far)
{
}

CubeCameraComponent::~CubeCameraComponent() = default;

void CubeCameraComponent::DoUpdate(FIRE::SceneObject& sceneObject, FIRE::Scene&)
{
    auto& transform = sceneObject.GetTransform();
    transform.SetPosition({0.0f, 2.0f, 10.0f});
    transform.SetLookAt({0.0f, 2.0f, 0.0f});
}
} // namespace examples
