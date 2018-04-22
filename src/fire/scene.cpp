#include "scene.h"

namespace Fire
{
    Scene::Scene(std::string const& sceneName)
        : m_name(sceneName)
    {
        
    }

    std::string Scene::GetName() const
    {
        return m_name;
    }    
} // namespace Fire
