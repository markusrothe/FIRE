#ifndef FIRE_CameraComponent_h
#define FIRE_CameraComponent_h

#include <FIRE/Component.h>
#include <FIRE/glmfwd.h>
namespace FIRE
{
class SceneObject;
class CameraComponent : public Component
{
public:
    CameraComponent(float fovy, float aspect, float near, float far);

    ~CameraComponent() override;

    void Setup(SceneObject& sceneObject) override;
    void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) override;
    std::optional<std::any> Receive(FIRE::Message msg, FIRE::SceneObject&) override;

private:
    virtual void DoUpdate(double deltaTime, SceneObject& sceneObject, Scene& scene);

    glm::mat4x4 m_view{};
    glm::mat4x4 m_proj;
};
} // namespace FIRE

#endif // FIRE_CameraComponent_h