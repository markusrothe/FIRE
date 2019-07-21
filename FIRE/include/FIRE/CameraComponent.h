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

    virtual ~CameraComponent() override;

    void Setup(SceneObject& sceneObject) override;
    void Update(double deltaTime, SceneObject& sceneObject, Scene& scene) override;

    glm::mat4x4 GetViewMatrix() const;
    glm::mat4x4 GetProjectionMatrix() const;

private:
    virtual void DoUpdate(double deltaTime, SceneObject& sceneObject, Scene& scene) = 0;

    glm::mat4x4 m_view;
    glm::mat4x4 m_proj;
};
} // namespace FIRE

#endif // FIRE_CameraComponent_h