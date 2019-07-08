#include <FIRE/Scene.h>

#include <FIRE/CameraComponent.h>
#include <FIRE/Renderable.h>

#include <algorithm>
namespace FIRE
{

SceneObject& Scene::CreateSceneObject(std::string name)
{
    m_sceneObjects.emplace_back(std::move(name));
    return m_sceneObjects.back();
}

void Scene::Update()
{
    for(auto& obj : m_sceneObjects)
    {
        obj.Update(*this);
    }
}

// CameraComponent const* Scene::GetCamera()
// {
//     for(auto& sceneObj : m_sceneObjects)
//     {
//         if(sceneObj.m_camera)
//         {
//             return sceneObj.m_camera.get();
//         }
//     }
//     return nullptr;
//}

} // namespace FIRE
