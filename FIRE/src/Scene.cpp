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

std::vector<std::shared_ptr<SceneComponent>> const& Scene::GetSceneComponents() const
{
    return m_sceneComponents;
}

} // namespace FIRE
