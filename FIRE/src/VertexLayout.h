#ifndef FIRE_VERTEXLAYOUT_H
#define FIRE_VERTEXLAYOUT_H

#include <cstdint>
namespace FIRE
{
enum class DrawMode
{
    NON_INDEXED,
    INDEXED
};

class VertexLayout
{
public:
    explicit VertexLayout(DrawMode mode)
        : drawMode(mode)
    {
    }

    virtual ~VertexLayout() = default;

    [[nodiscard]] DrawMode GetDrawMode() const
    {
        return drawMode;
    }

    virtual void BindLayout() = 0;
    virtual void ReleaseLayout() = 0;

    virtual void BufferData(uint32_t size, void* data) = 0;
    virtual void BufferIndexData(uint32_t size, void* data) = 0;
    virtual void BufferSubData(uint32_t offset, uint32_t size, void* data) = 0;
    virtual void AddVertexAttribute(uint32_t attribIndex, uint32_t size, uint32_t offset) = 0;

private:
    DrawMode drawMode;
};
} // namespace FIRE

#endif //FIRE_VERTEXLAYOUT_H
