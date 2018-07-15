#include "scene.h"
#include "findByName.h"
#include "sceneComponent.h"
#include <algorithm>
#include <sstream>

namespace
{
std::string const genericName = "scene_generic_";
unsigned int count = 0;

std::string CreateGenericName()
{
    std::stringstream ss;
    ss << genericName << count++;
    return ss.str();
}

} // namespace

namespace Fire
{
Scene::Scene(std::string const& sceneName)
    : m_sceneComponents()
    , m_name(sceneName.empty() ? CreateGenericName() : sceneName)
{
}

std::string Scene::GetName() const { return m_name; }

void Scene::AddSceneComponent(SceneComponent* sceneComponent)
{
    if(nullptr != sceneComponent)
    {
        m_sceneComponents.push_back(sceneComponent);
    }
}

SceneComponent* Scene::GetSceneComponent(std::string const& name) const
{
    return FindByName(m_sceneComponents, name, [](auto sceneComponent) {
        return sceneComponent ? sceneComponent->GetName() : "";
    });
}

unsigned int Scene::GetNumOfSceneComponents() const
{
    return m_sceneComponents.size();
}

void Scene::Update()
{
    for(auto sceneComponent : m_sceneComponents)
    {
        sceneComponent->Update();
    }
}

std::vector<Renderable*> Scene::GetRenderables() const
{
    std::vector<Renderable*> renderables;

    for(auto sceneComponent : m_sceneComponents)
    {
        for(auto renderable : sceneComponent->GetRenderables())
        {
            renderables.push_back(renderable);
        }
    }

    return renderables;
}
} // namespace Fire
