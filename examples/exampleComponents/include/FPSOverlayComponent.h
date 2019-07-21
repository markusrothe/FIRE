#ifndef examples_FPSOverlayComponent_h
#define examples_FPSOverlayComponent_h
#include <FIRE/OverlayComponent.h>
namespace examples
{
class SceneObject;
class Scene;
class FPSOverlayComponent : public FIRE::OverlayComponent
{
public:
    explicit FPSOverlayComponent(FIRE::TextRenderer& renderer);

private:
    std::optional<std::any> Receive(FIRE::Message msg) override;
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
};
} // namespace examples

#endif