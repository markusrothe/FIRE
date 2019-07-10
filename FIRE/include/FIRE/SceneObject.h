#ifndef FIRE_SceneObject_h
#define FIRE_SceneObject_h

#include <FIRE/Component.h>
#include <FIRE/Transform.h>
#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace FIRE
{
class Scene;
class SceneObject
{
public:
    explicit SceneObject(std::string name);
    ~SceneObject();

    SceneObject(SceneObject&& other);
    SceneObject& operator=(SceneObject&& other);

    Transform& GetTransform();

    std::string GetName() const;
    void Update(double deltaTime, Scene& scene);
    void AddComponent(std::unique_ptr<Component> component);

    std::optional<std::any> Send(Message msg);

private:
    std::string m_name;
    Transform m_transform;

    std::vector<std::unique_ptr<Component>> m_components;
};
} // namespace FIRE

#endif // FIRE_SceneObject_h