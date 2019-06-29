#ifndef SceneTemplate_SceneTemplate_h
#define SceneTemplate_SceneTemplate_h

#include <FIRE/Matrix.h>
#include <FIRE/Renderable.h>
#include <FIRE/SceneComponent.h>
#include <FIRE/Vector.h>
#include <vector>

namespace FIRE
{
class Camera;
class Window;
class MeshManager;
} // namespace FIRE

namespace SceneTemplate
{
class SceneTemplate : public FIRE::SceneComponent
{
public:
    explicit SceneTemplate(FIRE::Camera& cam, FIRE::Window& window, FIRE::MeshManager& factory);

    void Update(FIRE::Camera& cam) override;
    std::vector<FIRE::Renderable> CollectRenderables() const override;

private:
    FIRE::Vector3 m_lightPos;
    FIRE::Matrix4x4 m_proj;
    FIRE::Renderable m_plane;
    FIRE::Renderable m_lightCube;
};
} // namespace SceneTemplate
#endif // SceneTemplate_SceneTemplate_h
