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
        SceneManager(MaterialManager const& materialManager, KeyHandler& keyHandler,
            RenderableManager& renderableManager);

        void SetupScene(MaterialManager const& materialManager, RenderableManager& renderableManager, KeyHandler& keyHandler);

        void Update();

    private:
        std::vector<std::unique_ptr<SceneComponent> > m_sceneComponents;
        Camera m_cam;
    };
}

#endif // blocks_sceneManager_h
