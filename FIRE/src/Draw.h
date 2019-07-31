#ifndef FIRE_DRAW_H
#define FIRE_DRAW_H

namespace FIRE
{
class Mesh3D;
class Draw
{
public:
    virtual ~Draw() = default;
    virtual void Clear() = 0;
    virtual void DoDraw(Mesh3D* mesh) = 0;
    virtual void ToggleWireframe() = 0;
};
} // namespace FIRE

#endif //FIRE_DRAW_H
