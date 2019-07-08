#ifndef FIRE_SceneObject_h
#define FIRE_SceneObject_h

#include <FIRE/Transform.h>
#include <memory>
#include <string>

namespace FIRE
{
class CameraComponent;
class RenderingComponent;
class LightComponent;
class Scene;
class SceneObject
{
public:
    explicit SceneObject(std::string name);
    ~SceneObject();

    SceneObject(SceneObject&& other);
    SceneObject& operator=(SceneObject&& other);

    Transform& GetTransform();

    void Update(Scene& scene);

    void SetRenderingComponent(std::unique_ptr<RenderingComponent> rendering);
    void SetCameraComponent(std::unique_ptr<CameraComponent> camera);
    void SetLightComponent(std::unique_ptr<LightComponent> light);

private:
    std::string m_name;
    Transform m_transform;

public:
    std::unique_ptr<RenderingComponent> m_rendering;
    std::unique_ptr<CameraComponent> m_camera;
    std::unique_ptr<LightComponent> m_light;
};
} // namespace FIRE

#endif // FIRE_SceneObject_h