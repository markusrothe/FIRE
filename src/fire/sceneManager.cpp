#include "sceneManager.h"
#include "scene.h"

namespace Fire
{    
    SceneManager::SceneManager(Root const& root)
        : m_scenes()
    {
        
    }
    
    Scene& SceneManager::CreateScene(std::string_view const& sceneName)
    {
        m_scenes.emplace_back(sceneName);
    }
} // namespace Fire
