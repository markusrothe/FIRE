#ifndef FIRE_GLVERTEXLAYOUTBINDER_H
#define FIRE_GLVERTEXLAYOUTBINDER_H

#include "VertexLayout.h"
#include "VertexLayoutBinder.h"

namespace FIRE
{
class GLVertexLayoutBinder : public VertexLayoutBinder
{
public:
    void Bind(VertexLayout const& vertexLayout) override;
    void BindVertexBuffer() override;
    void BindIndexBuffer() override;
    void Release() override;

private:
    VertexLayout m_layout;
};
} // namespace FIRE

#endif //FIRE_GLVERTEXLAYOUTBINDER_H
