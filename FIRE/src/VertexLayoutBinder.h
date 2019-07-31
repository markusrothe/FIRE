#ifndef FIRE_VERTEXLAYOUTBINDER_H
#define FIRE_VERTEXLAYOUTBINDER_H

namespace FIRE
{
class VertexLayout;
class VertexLayoutBinder
{
public:
    virtual ~VertexLayoutBinder() = default;
    virtual void Bind(VertexLayout const& vertexLayout) = 0;
    virtual void BindVertexBuffer() = 0;
    virtual void BindIndexBuffer() = 0;
    virtual void Release() = 0;
};
} // namespace FIRE

#endif //FIRE_VERTEXLAYOUTBINDER_H
