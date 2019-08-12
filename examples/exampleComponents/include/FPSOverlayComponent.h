#ifndef examples_FPSOverlayComponent_h
#define examples_FPSOverlayComponent_h

#include <FIRE/Material.h>

#include <FIRE/RenderingComponent.h>

namespace FIRE
{
class AssetFacade;
class SceneObject;
class Scene;
} // namespace FIRE

namespace examples
{
class FPSOverlayComponent : public FIRE::RenderingComponent
{
public:
    explicit FPSOverlayComponent(FIRE::Renderer& renderer, FIRE::AssetFacade& assets);

private:
    std::optional<std::any> Receive(FIRE::Message msg, FIRE::SceneObject& sceneObject) override;

    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;

    FIRE::AssetFacade& assets;
};
} // namespace examples

#endif