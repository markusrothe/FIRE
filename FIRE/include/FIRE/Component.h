#ifndef FIRE_Component_h
#define FIRE_Component_h

namespace FIRE
{
class SceneObject;
class Scene;
class Component
{
public:
    virtual ~Component() = default;
    virtual void Update(SceneObject& sceneObject, Scene& scene) = 0;
};
} // namespace FIRE

#endif // FIRE_Component_h