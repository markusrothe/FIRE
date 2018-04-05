#include "sceneManager.h"
#include "camera.h"
#include "materialManager.h"
#include "keyhandler.h"

#include <algorithm>
#include <utility>

namespace blocks
{
    SceneManager::SceneManager(std::string const& materialConfigPath)
        : m_materialManager(materialConfigPath)
        , m_renderableManager()
        , m_fontManager()
        , m_scenes()
    {

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
        for (auto& scene : m_scenes)
        {
            scene->Update();
        }
    }

    void SceneManager::Render()
    {
        m_renderableManager.RenderRenderables();
    }
    
}
