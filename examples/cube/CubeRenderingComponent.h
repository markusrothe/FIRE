#ifndef FIRE_examples_CubeRenderingComponent_h
#define FIRE_examples_CubeRenderingComponent_h

#include <FIRE/Renderable.h>
#include <FIRE/RenderingComponent.h>
#include <FIRE/glmfwd.h>
#include <vector>

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
class CubeRenderingComponent : public FIRE::RenderingComponent
{
public:
    CubeRenderingComponent(FIRE::Renderer& renderer, FIRE::MeshManager& meshManager, FIRE::MaterialFactory& materialFactory);

private:
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg) override;

    FIRE::Renderable m_cube;
};
} // namespace examples

#endif //FIRE_examples_CubeRenderingComponent_h