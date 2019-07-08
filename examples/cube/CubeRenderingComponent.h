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
} // namespace FIRE

namespace examples
{
class CubeRenderingComponent : public FIRE::RenderingComponent
{
public:
    CubeRenderingComponent(FIRE::Renderer& renderer, FIRE::MeshManager& meshManager, FIRE::MaterialFactory& materialFactory);

protected:
    void DoUpdate(FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;

private:
    FIRE::Renderable m_cube;
};
} // namespace examples

#endif //FIRE_examples_CubeRenderingComponent_h