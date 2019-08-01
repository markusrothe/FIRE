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

    virtual void BufferData(size_t size, void* data) = 0;
    virtual void BufferIndexData(size_t size, void* data) = 0;
    virtual void BufferSubData(size_t offset, size_t size, void* data) = 0;
    virtual void AddVertexAttribute(uint32_t attribIndex, size_t size, size_t offset) = 0;

private:
    DrawMode drawMode;
};
} // namespace FIRE

#endif //FIRE_VERTEXLAYOUT_H
