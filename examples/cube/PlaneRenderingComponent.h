#ifndef examples_PlaneRenderingComponent_h
#define examples_PlaneRenderingComponent_h
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
class PlaneRenderingComponent : public FIRE::RenderingComponent
{
public:
    PlaneRenderingComponent(
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

#endif //examples_PlaneRenderingComponent_h