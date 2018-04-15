#include "sceneManager.h"
#include "scene.h"
#include "root.h"

namespace Fire
{    
    SceneManager::SceneManager(Root const& root)
        : m_root(root)
        , m_scenes()
    {

    }
    
    Scene& SceneManager::CreateScene(std::string const& sceneName)
    {
        m_scenes.emplace_back(sceneName);
        return m_scenes.back();
    }

    void SceneManager::Update()
    {
    }
} // namespace Fire
