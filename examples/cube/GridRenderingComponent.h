#ifndef examples_GridRenderingComponent_h
#define examples_GridRenderingComponent_h
#include <FIRE/Renderable.h>
#include <FIRE/RenderingComponent.h>

namespace FIRE
{
class Window;
class MeshManager;
class Camera;
class MaterialFactory;
class Message;
} // namespace FIRE

namespace examples
{
class GridRenderingComponent : public FIRE::RenderingComponent
{
public:
    GridRenderingComponent(
        FIRE::SceneObject& sceneObject,
        FIRE::Renderer& renderer,
        FIRE::MeshManager& meshManager,
        FIRE::MaterialFactory& materialFactory);

private:
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg) override;

    FIRE::Renderable m_plane;
};
} // namespace examples

#endif //examples_GridRenderingComponent_h