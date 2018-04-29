#ifndef fire_scenecomponent_h
#define fire_scenecomponent_h

#include <string>

namespace Fire
{
    class SceneComponent
    {
    public:
        virtual std::string GetName() const = 0;

        virtual void Update() = 0;
    };
} // namespace Fire

#endif // fire_scenecomponent_h