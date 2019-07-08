#include <FIRE/CameraComponent.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Transform.h>

namespace FIRE
{
CameraComponent::CameraComponent(float fovy, float aspect, float near, float far)
    : m_proj(glm::perspective(fovy, aspect, near, far))
{
}

void CameraComponent::Update(SceneObject& sceneObject, Scene& scene)
{
    DoUpdate(sceneObject, scene);
    auto& transform = sceneObject.GetTransform();
    m_view = glm::lookAt(transform.Position(), transform.LookAt(), transform.Up());
}

glm::mat4x4 CameraComponent::GetViewMatrix() const
{
    return m_view;
}

glm::mat4x4 CameraComponent::GetProjectionMatrix() const
{
    return m_proj;
}

CameraComponent::~CameraComponent() = default;

} // namespace FIRE
