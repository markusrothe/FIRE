#ifndef fire_scenecomponent_h
#define fire_scenecomponent_h

#include <string>
#include <vector>

namespace Fire
{
class Renderable;

class SceneComponent
{
public:
    virtual std::string GetName() const = 0;

    virtual void Update() = 0;

    virtual std::vector<Renderable*> GetRenderables() = 0;
};
} // namespace Fire

#endif // fire_scenecomponent_h
