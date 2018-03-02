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
        : m_scenes()
        , m_cam(glm::vec3(0, 100, -20), 45, 2, 10000, 1200, 600)
    {
        keyHandler.AddListener(&m_cam);
    }

    Camera const& SceneManager::GetCam() const
    {
        return m_cam;
    }

    Scene* SceneManager::CreateScene(std::string const& name)
    {
        auto scene = std::make_unique<Scene>(name);
        auto const scenePtr = scene.get();
        m_scenes.push_back(std::move(scene));

        return scenePtr;
    }

    void SceneManager::Update()
    {
        m_cam.Update();

        for (auto& scene : m_scenes)
        {
            scene->Update();
        }
    }
}
