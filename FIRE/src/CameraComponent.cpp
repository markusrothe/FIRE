#include <FIRE/CameraComponent.h>
#include <FIRE/Message.h>
#include <FIRE/SceneObject.h>
#include <FIRE/Transform.h>

namespace FIRE
{
CameraComponent::CameraComponent(float fovy, float aspect, float near, float far)
    : m_proj(glm::perspective(fovy, aspect, near, far))
{
}

CameraComponent::~CameraComponent() = default;

void CameraComponent::Setup(SceneObject&)
{
}

void CameraComponent::Update(double deltaTime, SceneObject& sceneObject, Scene& scene)
{
    auto& transform = sceneObject.GetTransform();
    m_view = glm::lookAt(transform.Position(), transform.LookAt(), transform.Up());
    DoUpdate(deltaTime, sceneObject, scene);
}

std::optional<std::any> CameraComponent::Receive(FIRE::Message msg, FIRE::SceneObject&)
{
    if(msg.id == FIRE::MessageID::GetViewMatrix)
    {
        return m_view;
    }
    else if(msg.id == FIRE::MessageID::GetProjectionMatrix)
    {
        return m_proj;
    }

    return std::nullopt;
}

void CameraComponent::DoUpdate(double, SceneObject&, Scene&)
{
}
} // namespace FIRE
