#ifndef FIRE_GLDRAW_H
#define FIRE_GLDRAW_H
#include "Draw.h"
#include <cstdint>
namespace FIRE
{
class GLDraw : public Draw
{
public:
    GLDraw();
    void Clear() override;
    void DoDraw(VertexLayout& layout, MeshPrimitives primitives, uint32_t count) override;
    void DoDrawIndexed(VertexLayout& layout, MeshPrimitives primitives, uint32_t count) override;
    void ToggleWireframe() override;
};
} // namespace FIRE

#endif //FIRE_GLDRAW_H
