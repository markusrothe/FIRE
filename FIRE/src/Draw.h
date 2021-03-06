#ifndef FIRE_DRAW_H
#define FIRE_DRAW_H
#include <FIRE/MeshType.h>
#include <cstdint>
namespace FIRE
{
class VertexLayout;
class Draw
{
public:
    virtual ~Draw() = default;
    virtual void Clear() = 0;
    virtual void DoDraw(VertexLayout& layout, MeshPrimitives primitives, uint32_t count) = 0;
    virtual void DoDrawIndexed(VertexLayout& layout, MeshPrimitives primitives, uint32_t count) = 0;
    virtual void ToggleWireframe() = 0;
};
} // namespace FIRE

#endif //FIRE_DRAW_H
