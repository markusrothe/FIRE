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

    RenderableManager& SceneManager::GetRenderableManager()
    {
        return m_renderableManager;
    }

    MaterialManager& SceneManager::GetMaterialManager()
    {
        return m_materialManager;
    }

    FontManager& SceneManager::GetFontManager()
    {
        return m_fontManager;
    }

    Scene& SceneManager::CreateScene(std::string const& name)
    {
        auto scene = std::make_unique<Scene>(name);
        m_scenes.push_back(std::move(scene));

        auto const it = std::find_if(std::begin(m_scenes), std::end(m_scenes)
            , [&](std::unique_ptr<Scene> const& scene) { return name.compare(scene->GetName()) == 0; });

        return *(*it);
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
