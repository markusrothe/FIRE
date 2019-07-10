#ifndef FIRE_OverlayComponent_h
#define FIRE_OverlayComponent_h

#include <FIRE/Component.h>

namespace FIRE
{
class SceneObject;
class Scene;
class TextRenderer;
class OverlayComponent : public Component
{
public:
    explicit OverlayComponent(TextRenderer& renderer);

    virtual ~OverlayComponent();

    void Update(SceneObject& sceneObject, Scene& scene) override;

protected:
    TextRenderer& renderer;

private:
    virtual void DoUpdate(SceneObject& sceneObject, Scene& scene) = 0;
};
} // namespace FIRE

#endif // FIRE_OverlayComponent_h