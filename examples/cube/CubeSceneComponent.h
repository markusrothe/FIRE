#ifndef FIRE_examples_CubeSceneComponent_h
#define FIRE_examples_CubeSceneComponent_h

#include <FIRE/Matrix.h>
#include <FIRE/Renderable.h>
#include <FIRE/SceneComponent.h>
#include <vector>

namespace FIRE
{
class Window;
class MeshManager;
class Camera;
} // namespace FIRE

namespace examples
{
class CubeSceneComponent : public FIRE::SceneComponent
{
public:
    CubeSceneComponent(FIRE::Window const& window, FIRE::MeshManager& meshManager);

    void Update(FIRE::Camera& cam) override;

    std::vector<FIRE::Renderable> CollectRenderables() const override;

private:
    FIRE::Matrix4x4 m_proj;
    FIRE::Renderable m_cube;
};
} // namespace examples

#endif //FIRE_examples_CubeSceneComponent_h