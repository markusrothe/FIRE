#ifndef examples_CubeOverlayComponent_h
#define examples_CubeOverlayComponent_h
#include <FIRE/OverlayComponent.h>

namespace examples
{
class SceneObject;
class Scene;
class CubeOverlayComponent : public FIRE::OverlayComponent
{
public:
    explicit CubeOverlayComponent(FIRE::TextRenderer& renderer);

private:
    std::optional<std::any> Receive(FIRE::Message msg) override;
    void DoUpdate(double deltaTime, FIRE::SceneObject& sceneObject, FIRE::Scene& scene) override;
};
} // namespace examples

#endif // examples_CubeOverlayComponent_h