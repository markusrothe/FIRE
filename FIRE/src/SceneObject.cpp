#include <FIRE/CameraComponent.h>
#include <FIRE/LightComponent.h>
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

Transform& SceneObject::GetTransform()
{
    return m_transform;
}

void SceneObject::Update(Scene& scene)
{
    for(auto& component : m_components)
    {
        component->Update(*this, scene);
    }
}
} // namespace FIRE
