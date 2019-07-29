#ifndef examples_FPSOverlayComponent_h
#define examples_FPSOverlayComponent_h
#include <FIRE/RenderingComponent.h>
namespace examples
{
class SceneObject;
class Scene;
class FPSOverlayComponent : public FIRE::RenderingComponent
{
public:
    explicit FPSOverlayComponent(FIRE::Renderer& renderer);

private:
    std::optional<std::any> Receive(FIRE::Message msg, FIRE::SceneObject& sceneObject) override;
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
};
} // namespace examples

#endif