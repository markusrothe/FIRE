#ifndef FIRE_examples_Mesh3DRenderingComponent_h
#define FIRE_examples_Mesh3DRenderingComponent_h

#include <FIRE/Renderable.h>
#include <FIRE/RenderingComponent.h>
#include <FIRE/glmfwd.h>

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
class Mesh3DRenderingComponent : public FIRE::RenderingComponent
{
public:
    Mesh3DRenderingComponent(FIRE::Renderer& renderer, FIRE::MeshManager& meshManager, FIRE::MaterialFactory& materialFactory);

private:
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg) override;

    FIRE::Renderable m_cube;
    std::vector<FIRE::Renderable> renderables;
};
} // namespace examples

#endif