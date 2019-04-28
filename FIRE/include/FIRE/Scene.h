#ifndef FIRE_Scene_h
#define FIRE_Scene_h

#include <memory>
#include <string>
#include <vector>

namespace FIRE
{
class Camera;
class Renderable;
class SceneComponent
{
public:
    explicit SceneComponent(std::string name);
    std::string Name() const;
    void AddRenderable(std::shared_ptr<Renderable> const& renderable);

    std::vector<std::shared_ptr<Renderable>> GetRenderables() const;

private:
    std::string m_name;
    std::vector<std::shared_ptr<Renderable>> m_renderables;
};

class Scene
{
public:
    std::shared_ptr<SceneComponent> NewSceneComponent(std::string const& name);

    std::vector<std::shared_ptr<SceneComponent>> const& GetSceneComponents() const;

private:
    std::vector<std::shared_ptr<SceneComponent>> m_sceneComponents;
};

} // namespace FIRE

#endif
