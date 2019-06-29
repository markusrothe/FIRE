#ifndef FIRE_SceneComponent_h
#define FIRE_SceneComponent_h

#include <FIRE/Renderable.h>
#include <vector>
namespace FIRE
{

class Camera;
class SceneComponent
{
public:
    virtual ~SceneComponent()
    {
    }

    virtual void Update(FIRE::Camera& cam) = 0;
    virtual std::vector<FIRE::Renderable> CollectRenderables() const = 0;
};
} // namespace FIRE
#endif // FIRE_SceneComponent_h
