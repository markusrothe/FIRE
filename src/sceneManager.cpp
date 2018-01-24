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
        SetupScene(materialManager, renderableManager, keyHandler);
        keyHandler.AddListener(&m_cam);
    }

    void SceneManager::SetupScene(MaterialManager const& materialManager, RenderableManager& renderableManager, KeyHandler& keyHandler)
    {
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
