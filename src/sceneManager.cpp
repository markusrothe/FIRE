#include "sceneManager.h"
#include "camera.h"
#include "materialManager.h"
#include "keyhandler.h"

#include <algorithm>
#include <utility>

namespace blocks
{
    Scene* SceneManager::CreateScene(std::string const& name)
    {
        auto scene = std::make_unique<Scene>(name);
        auto const scenePtr = scene.get();
        m_scenes.push_back(std::move(scene));

        return scenePtr;
    }

    void SceneManager::Update()
    {
        for (auto& scene : m_scenes)
        {
            scene->Update();
        }
    }
}
