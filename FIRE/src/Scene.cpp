#include <FIRE/Scene.h>

#include <FIRE/CameraComponent.h>
#include <FIRE/Message.h>
#include <FIRE/Renderable.h>

#include <algorithm>
namespace FIRE
{

SceneObject& Scene::CreateSceneObject(std::string name)
{
    m_sceneObjects.emplace_back(std::move(name));
    return m_sceneObjects.back();
}

void Scene::Update(double deltaTime)
{
    for(auto& obj : m_sceneObjects)
    {
        obj.Update(deltaTime, *this);
    }
}

std::optional<std::any> Scene::Send(Message msg)
{
    for(auto& obj : m_sceneObjects)
    {
        std::optional<std::any> response = obj.Send(msg);
        if(response)
        {
            return response;
        }
    }

    return std::nullopt;
}

} // namespace FIRE
