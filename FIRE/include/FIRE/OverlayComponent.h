#ifndef FIRE_OVERLAYCOMPONENT_H
#define FIRE_OVERLAYCOMPONENT_H
#include <FIRE/Component.h>
#include <FIRE/TextOverlay.h>
namespace FIRE
{
class OverlaySubmitter;
class OverlayComponent : public Component
{
public:
    explicit OverlayComponent(OverlaySubmitter& overlaySubmitter, std::vector<TextOverlay> overlays);
    void Setup(SceneObject& sceneObject) override;
    void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) override;
    std::optional<std::any> Receive(Message const& msg, SceneObject& sceneObject) override;

protected:
    OverlaySubmitter& overlaySubmitter;
    std::vector<TextOverlay> overlays;

private:
    virtual void DoUpdate(double deltaTime, SceneObject& sceneObject, Scene& scene);
};
} // namespace FIRE
#endif //FIRE_OVERLAYCOMPONENT_H
