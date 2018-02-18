#ifndef blocks_sceneManager_h
#define blocks_sceneManager_h

#include "camera.h"
#include "sceneComponent.h"
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

        void AddSceneComponent(std::shared_ptr<SceneComponent> const& sceneComponent);

        void Update();

    private:
        std::vector<std::shared_ptr<SceneComponent> > m_sceneComponents;
        Camera m_cam;
    };
}

#endif // blocks_sceneManager_h
