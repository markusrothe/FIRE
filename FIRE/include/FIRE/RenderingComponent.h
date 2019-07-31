#ifndef FIRE_RenderingComponent_h
#define FIRE_RenderingComponent_h

#include "Renderer.h"
#include <FIRE/Component.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>

namespace FIRE
{
class RenderingComponent : public Component
{
public:
    explicit RenderingComponent(Renderer& renderer);
    virtual ~RenderingComponent() override;

    void Setup(SceneObject& sceneObject) override;
    void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) override;

protected:
    Renderer& m_renderer;

private:
    virtual void DoUpdate(double deltaTime, SceneObject& sceneObject, Scene& scene) = 0;
};
} // namespace FIRE

#endif // FIRE_RenderingComponent_h