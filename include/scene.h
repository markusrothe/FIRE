#ifndef blocks_scene_h
#define blocks_scene_h

#include "sceneComponent.h"
#include <memory>
#include <vector>
#include <string>

namespace blocks
{
    class SceneManager;
    
    class Scene
    {
    public:
        explicit Scene(std::string const& name);

        void AddSceneComponent(std::unique_ptr<SceneComponent>& sceneComponent);

        void Update();

    private:
        std::string const m_name;
        
        std::vector< std::unique_ptr<SceneComponent> > m_sceneComponents;
    };
    
} // namespace blocks

#endif
