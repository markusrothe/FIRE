#include "VertexLayout.h"

namespace FIRE
{
VertexLayout::VertexLayout(uint32_t id, uint32_t vertexBuffer, uint32_t indexBuffer)
    : m_id(id)
    , m_vertexBuffer(vertexBuffer)
    , m_indexBuffer(indexBuffer)
{
}
} // namespace FIRE
