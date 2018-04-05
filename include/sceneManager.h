#ifndef blocks_sceneManager_h
#define blocks_sceneManager_h

#include "scene.h"
#include "fontManager.h"
#include "renderableManager.h"
#include "materialManager.h"
#include <vector>
#include <memory>

namespace blocks
{
    class SceneManager
    {
    public:
        explicit SceneManager(std::string const& materialConfigPath);
        
        Scene* CreateScene(std::string const& name);

        void Update();

        void Render();
        
    private:
        MaterialManager m_materialManager;
        RenderableManager m_renderableManager;
        FontManager m_fontManager;
        
        std::vector<std::unique_ptr<Scene> > m_scenes;
    };
}

#endif // blocks_sceneManager_h
