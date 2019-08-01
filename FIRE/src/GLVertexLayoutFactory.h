#ifndef FIRE_GLVERTEXLAYOUTFACTORY_H
#define FIRE_GLVERTEXLAYOUTFACTORY_H

#include "VertexLayoutFactory.h"
#include <FIRE/TextOverlay.h>
#include <cstdint>
#include <string>
#include <unordered_map>
namespace FIRE
{
class GLVertexLayoutFactory : public VertexLayoutFactory
{
public:
    VertexLayout& CreateStaticIndexedLayout(Renderable const& renderable) override;
    VertexLayout& CreateDynamicLayout(TextOverlay const& overlay) override;

public:
private:
    std::unordered_map<std::string, std::unique_ptr<VertexLayout>> m_cache{};
};
} // namespace FIRE

#endif //FIRE_GLVERTEXLAYOUTFACTORY_H
