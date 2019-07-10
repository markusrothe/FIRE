#include <FIRE/CameraComponent.h>
#include <FIRE/LightComponent.h>
#include <FIRE/Message.h>
#include <FIRE/RenderingComponent.h>
#include <FIRE/SceneObject.h>

namespace FIRE
{
SceneObject::SceneObject(std::string name)
    : m_name(std::move(name))
{
}

SceneObject::~SceneObject() = default;
SceneObject::SceneObject(SceneObject&& other) = default;
SceneObject& SceneObject::operator=(SceneObject&& other) = default;

void SceneObject::AddComponent(std::unique_ptr<Component> component)
{
    m_components.push_back(std::move(component));
}

std::string SceneObject::GetName() const
{
    return m_name;
}

Transform& SceneObject::GetTransform()
{
    return m_transform;
}

void SceneObject::Update(double deltaTime, Scene& scene)
{
    for(auto& component : m_components)
    {
        component->Update(deltaTime, *this, scene);
    }
}

std::optional<std::any> SceneObject::Send(Message msg)
{
    for(auto& component : m_components)
    {
        auto response = component->Receive(msg);
        if(response)
        {
            return response;
        }
    }

    return std::nullopt;
}
} // namespace FIRE
