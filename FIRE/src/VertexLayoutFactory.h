#ifndef FIRE_VERTEXLAYOUTFACTORY_H
#define FIRE_VERTEXLAYOUTFACTORY_H

#include "VertexLayout.h"
#include <memory>

namespace FIRE
{
struct Renderable;
class TextOverlay;
class VertexLayoutFactory
{
public:
    virtual ~VertexLayoutFactory() = default;
    virtual VertexLayout& CreateStaticIndexedLayout(Renderable const& renderable) = 0;
    virtual VertexLayout& CreateDynamicLayout(TextOverlay const& overlay) = 0;
};
} // namespace FIRE
#endif //FIRE_VERTEXLAYOUTFACTORY_H
