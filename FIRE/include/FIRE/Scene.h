#ifndef FIRE_Scene_h
#define FIRE_Scene_h

#include <FIRE/Camera.h>
#include <memory>
#include <vector>

namespace FIRE
{

class SceneComponent;
struct Renderable;
class Scene
{
public:
    explicit Scene(FIRE::Camera cam);

    FIRE::Camera& GetCamera();

    void AddSceneComponent(std::shared_ptr<SceneComponent> const& sceneComponent);
    void Update();
    std::vector<Renderable> CollectRenderables() const;

private:
    FIRE::Camera m_cam;
    std::vector<std::shared_ptr<SceneComponent>> m_sceneComponents;
};

} // namespace FIRE

#endif
