#ifndef FIRE_DRAWMOCK_H
#define FIRE_DRAWMOCK_H

#include "Draw.h"
#include <gmock/gmock.h>

namespace FIRE_tests
{
class DrawMock : public FIRE::Draw
{
public:
    MOCK_METHOD0(Clear, void(void));
    MOCK_METHOD3(DoDraw, void(FIRE::VertexLayout& layout, FIRE::MeshPrimitives primitives, uint32_t count));
    MOCK_METHOD3(DoDrawIndexed, void(FIRE::VertexLayout& layout, FIRE::MeshPrimitives primitives, uint32_t count));
    MOCK_METHOD0(ToggleWireframe, void(void));
};
} // namespace FIRE_tests

#endif //FIRE_DRAWMOCK_H