#include "sceneManager.h"
#include "camera.h"
#include "materialManager.h"
#include "keyhandler.h"

#include <algorithm>
#include <utility>

namespace blocks
{
    SceneManager::SceneManager(MaterialManager const& materialManager, KeyHandler& keyHandler
                               , RenderableManager& renderableManager)
        : m_sceneComponents()
        , m_cam(glm::vec3(0, 100, -20), 45, 2, 10000, 1200, 600)
    {
        keyHandler.AddListener(&m_cam);
    }

    Camera const& SceneManager::GetCam() const
    {
        return m_cam;
    }

    void SceneManager::AddSceneComponent(std::shared_ptr<SceneComponent> const& sceneComponent)
    {
        m_sceneComponents.push_back(sceneComponent);
    }

    void SceneManager::Update()
    {
        m_cam.Update();

        for (auto& sceneComponent : m_sceneComponents)
        {
            sceneComponent->Update();
        }
    }
}
