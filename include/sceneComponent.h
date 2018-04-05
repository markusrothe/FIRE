#ifndef blocks_scenecomponent_h
#define blocks_scenecomponent_h

namespace blocks
{
    class SceneComponent
    {
    public:
        virtual ~SceneComponent() {}

        virtual void Update() = 0;
    };
}

#endif // blocks_scenecomponent_h
