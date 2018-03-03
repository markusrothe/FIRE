#ifndef blocks_sceneManager_h
#define blocks_sceneManager_h

#include "camera.h"
#include "sceneComponent.h"
#include "scene.h"
#include <vector>
#include <memory>

namespace blocks
{
    class SceneManager
    {
    public:
        Scene* CreateScene(std::string const& name);

        void Update();

    private:
        std::vector<std::unique_ptr<Scene> > m_scenes;
    };
}

#endif // blocks_sceneManager_h
