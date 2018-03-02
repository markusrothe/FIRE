#ifndef blocks_sceneManager_h
#define blocks_sceneManager_h

#include "camera.h"
#include "sceneComponent.h"
#include "scene.h"
#include <vector>
#include <memory>

namespace blocks
{
    class MaterialManager;
    class KeyHandler;
    class RenderableManager;

    class SceneManager
    {
    public:
        SceneManager(MaterialManager const& materialManager, KeyHandler& keyHandler, RenderableManager& renderableManager);

        Camera const& GetCam() const;

        Scene* CreateScene(std::string const& name);

        void Update();

    private:
        std::vector<std::unique_ptr<Scene> > m_scenes;
        Camera m_cam;
    };
}

#endif // blocks_sceneManager_h
