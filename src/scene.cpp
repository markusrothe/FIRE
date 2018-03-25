#include "scene.h"


namespace blocks
{
    Scene::Scene(std::string const& name)
        : m_name(name)
        , m_sceneComponents()
    {

    }

    void Scene::AddSceneComponent(std::unique_ptr<SceneComponent>& sceneComponent)
    {
        m_sceneComponents.push_back(std::move(sceneComponent));
    }

    void Scene::Update()
    {
        for (auto& component : m_sceneComponents)
        {
            component->Update();
        }
    }

} // namespace blocks
 
