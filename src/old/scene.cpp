#include "scene.h"


namespace blocks
{
    Scene::Scene(std::string const& name)
        : m_name(name)
        , m_sceneComponents()
    {

    }

    std::string Scene::GetName() const
    {
        return m_name;
    }

    void Scene::AddSceneComponent(std::unique_ptr<SceneComponent>&& sceneComponent)
    {
        if(sceneComponent)
        {            
            m_sceneComponents.push_back(std::move(sceneComponent));
        }

    }

    void Scene::Update()
    {
        for (auto& component : m_sceneComponents)
        {
            component->Update();
        }
    }

} // namespace blocks
 
