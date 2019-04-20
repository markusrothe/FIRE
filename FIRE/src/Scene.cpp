#include <FIRE/Scene.h>
#include <algorithm>
namespace FIRE
{

SceneComponent::SceneComponent(std::string name)
    : m_name(std::move(name))
{
}

std::string SceneComponent::Name() const
{
    return m_name;
}

void SceneComponent::AddRenderable(std::shared_ptr<Renderable> const& renderable)
{
    m_renderables.push_back(renderable);
}

void SceneComponent::AddCamera(std::shared_ptr<Camera> const& cam)
{
    m_cam = cam;
}

std::vector<std::shared_ptr<Renderable>> SceneComponent::GetRenderables() const
{
    return m_renderables;
}

std::shared_ptr<SceneComponent> Scene::NewSceneComponent(std::string const& name)
{
    auto newSceneComponent = std::make_shared<SceneComponent>(name);
    m_sceneComponents.push_back(newSceneComponent);
    return newSceneComponent;
}

std::shared_ptr<SceneComponent> Scene::GetSceneComponent(std::string const& name) const
{
    auto const it = std::find_if(
        std::begin(m_sceneComponents), std::end(m_sceneComponents), [name](auto const& comp) {
            return name == comp->Name();
        });

    if(it == std::end(m_sceneComponents))
    {
        return nullptr;
    }

    return *it;
}

std::vector<std::shared_ptr<SceneComponent>> const& Scene::GetSceneComponents() const
{
    return m_sceneComponents;
}

} // namespace FIRE
