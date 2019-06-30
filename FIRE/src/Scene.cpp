#include <FIRE/Scene.h>

#include <FIRE/Renderable.h>
#include <FIRE/SceneComponent.h>
#include <algorithm>
namespace FIRE
{
Scene::Scene(FIRE::Camera cam)
    : m_cam(cam)
{
}

FIRE::Camera& Scene::GetCamera()
{
    return m_cam;
}

void Scene::AddSceneComponent(std::shared_ptr<SceneComponent> const& sceneComponent)
{
    m_sceneComponents.push_back(sceneComponent);
}

void Scene::Update()
{
    for(auto& sceneComponent : m_sceneComponents)
    {
        sceneComponent->Update(m_cam);
    }
}

std::vector<Renderable> Scene::CollectRenderables() const
{
    std::vector<Renderable> renderables;
    for(auto& sceneComponent : m_sceneComponents)
    {
        auto const sceneComponentRenderables = sceneComponent->CollectRenderables();
        renderables.insert(renderables.end(), sceneComponentRenderables.begin(), sceneComponentRenderables.end());
    }
    return renderables;
}

} // namespace FIRE
