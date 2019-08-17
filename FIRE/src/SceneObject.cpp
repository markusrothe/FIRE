
#include <FIRE/Message.h>
#include <FIRE/SceneObject.h>

namespace FIRE
{
SceneObject::SceneObject(std::string name)
    : m_name(std::move(name))
{
}

SceneObject::~SceneObject() = default;
SceneObject::SceneObject(SceneObject&& other) noexcept = default;
SceneObject& SceneObject::operator=(SceneObject&& other) noexcept = default;

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

void SceneObject::Setup()
{
    for(auto& component : m_components)
    {
        component->Setup(*this);
    }
}

void SceneObject::Update(double deltaTime, Scene& scene)
{
    m_transform.Translate(m_transform.Acceleration());
    for(auto& component : m_components)
    {
        component->Update(deltaTime, *this, scene);
    }
}

std::optional<std::any> SceneObject::Send(Message const& msg)
{
    for(auto& component : m_components)
    {
        auto response = component->Receive(msg, *this);
        if(response)
        {
            return response;
        }
    }

    return std::nullopt;
}
} // namespace FIRE
