#ifndef FIRE_RenderingComponent_h
#define FIRE_RenderingComponent_h

#include <FIRE/Component.h>
#include <FIRE/Renderable.h>
#include <vector>
namespace FIRE
{
class RenderableSubmitter;
class Scene;
class SceneObject;
class RenderingComponent : public Component
{
public:
    explicit RenderingComponent(RenderableSubmitter& submitter, std::vector<Renderable> renderables);
    ~RenderingComponent() override;

    void Setup(SceneObject& sceneObject) override;
    void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) override;
    std::optional<std::any> Receive(Message msg, SceneObject& sceneObject) override;

protected:
    RenderableSubmitter& m_renderableSubmitter;
    std::vector<Renderable> m_renderables;

private:
    virtual void DoUpdate(double deltaTime, SceneObject& sceneObject, Scene& scene);
};
} // namespace FIRE

#endif // FIRE_RenderingComponent_h