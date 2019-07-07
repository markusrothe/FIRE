#ifndef FIRE_SceneComponent_h
#define FIRE_SceneComponent_h

#include <FIRE/Renderable.h>
#include <FIRE/TextOverlay.h>
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

    virtual void Update(Camera& cam) = 0;
    virtual std::vector<Renderable> CollectRenderables() const
    {
        return {};
    }

    virtual std::vector<TextOverlay> CollectTextOverlays() const
    {
        return {};
    }
};
} // namespace FIRE
#endif // FIRE_SceneComponent_h
