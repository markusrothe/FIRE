#ifndef FIRE_RenderingComponent_h
#define FIRE_RenderingComponent_h

#include <FIRE/Component.h>
#include <FIRE/Renderer.h>
#include <FIRE/Scene.h>
#include <FIRE/SceneObject.h>

namespace FIRE
{
class RenderingComponent : public Component
{
public:
    explicit RenderingComponent(Renderer& renderer);
    void Update(SceneObject& sceneObject, Scene& scene);

    virtual ~RenderingComponent() override;

protected:
    Renderer& m_renderer;

private:
    virtual void DoUpdate(SceneObject& sceneObject, Scene& scene) = 0;
};
} // namespace FIRE

#endif // FIRE_RenderingComponent_h