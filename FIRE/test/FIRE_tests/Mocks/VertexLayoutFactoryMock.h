#ifndef FIRE_VERTEXLAYOUTFACTORYMOCK_H
#define FIRE_VERTEXLAYOUTFACTORYMOCK_H

#include "VertexLayoutFactory.h"
#include <gmock/gmock.h>
namespace FIRE_tests
{
class VertexLayoutFactoryMock : public FIRE::VertexLayoutFactory
{
public:
    MOCK_METHOD1(CreateStaticIndexedLayout, FIRE::VertexLayout&(FIRE::Renderable const&));
    MOCK_METHOD1(CreateDynamicLayout, FIRE::VertexLayout&(FIRE::TextOverlay const&));
};
} // namespace FIRE_tests

#endif //FIRE_VERTEXLAYOUTFACTORYMOCK_H
