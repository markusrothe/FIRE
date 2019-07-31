#ifndef FIRE_VERTEXLAYOUT_H
#define FIRE_VERTEXLAYOUT_H
#include <cstdint>
namespace FIRE
{
class VertexLayout
{
public:
    VertexLayout() = default;
    VertexLayout(uint32_t id, uint32_t vertexBuffer, uint32_t indexBuffer);

    uint32_t m_id;
    uint32_t m_vertexBuffer;
    uint32_t m_indexBuffer;
};
} // namespace FIRE

#endif //FIRE_VERTEXLAYOUT_H
