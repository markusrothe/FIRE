#ifndef fire_scenemanager_h
#define fire_scenemanager_h

#include <string>
#include <vector>

namespace Fire
{
    class Root;
    class Scene;

    class SceneManager
    {
    public:
        explicit SceneManager(Root const& root);

        Scene& CreateScene(std::string const& sceneName);

        void Update();
    private:
        Root const& m_root;
        std::vector<Scene> m_scenes;
    };

} // namespace Fire

#endif
