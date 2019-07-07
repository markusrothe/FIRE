#ifndef SceneTemplate_SceneTemplate_h
#define SceneTemplate_SceneTemplate_h

#include <FIRE/Renderable.h>
#include <FIRE/SceneComponent.h>
#include <FIRE/TextOverlay.h>
#include <vector>

namespace FIRE
{
class Camera;
class Window;
class MeshManager;
class MaterialFactory;
} // namespace FIRE

namespace SceneTemplate
{
class SceneTemplate : public FIRE::SceneComponent
{
public:
    explicit SceneTemplate(FIRE::Camera& cam, FIRE::Window& window, FIRE::MeshManager& meshManager, FIRE::MaterialFactory& materialFactory);

    void Update(FIRE::Camera& cam) override;

    std::vector<FIRE::Renderable> CollectRenderables() const override;
    std::vector<FIRE::TextOverlay> CollectTextOverlays() const override;

private:
    glm::vec3 m_lightPos;
    glm::mat4x4 m_proj;
    FIRE::Renderable m_plane;
    FIRE::Renderable m_lightCube;
};
} // namespace SceneTemplate
#endif // SceneTemplate_SceneTemplate_h
