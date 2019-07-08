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

void SceneObject::SetRenderingComponent(std::unique_ptr<RenderingComponent> rendering)
{
    m_rendering = std::move(rendering);
}

void SceneObject::SetCameraComponent(std::unique_ptr<CameraComponent> camera)
{
    m_camera = std::move(camera);
}

void SceneObject::SetLightComponent(std::unique_ptr<LightComponent> light)
{
    m_light = std::move(light);
}

Transform& SceneObject::GetTransform()
{
    return m_transform;
}

void SceneObject::Update(Scene& scene)
{
    if(m_rendering)
    {
        m_rendering->Update(*this, scene);
    }

    if(m_camera)
    {
        m_camera->Update(*this, scene);
    }

    if(m_light)
    {
        //  m_light->Update(*this, scene);
    }
}
} // namespace FIRE
