#ifndef FIRE_GLVERTEXLAYOUT_H
#define FIRE_GLVERTEXLAYOUT_H

#include "VertexLayout.h"
#include <cstdint>

namespace FIRE
{
class GLVertexLayout : public VertexLayout
{
public:
    enum class BufferUsage
    {
        STATIC,
        DYNAMIC
    };

    explicit GLVertexLayout(DrawMode mode);
    ~GLVertexLayout() override;
    void BindLayout() override;
    void ReleaseLayout() override;

    void BufferData(size_t size, void* data) override;
    void BufferIndexData(size_t size, void* data) override;
    void BufferSubData(size_t offset, size_t size, void* data) override;
    void AddVertexAttribute(uint32_t attribIndex, size_t size, size_t offset) override;

private:
    uint32_t m_vao{0u};
    uint32_t m_vbo{0u};
    uint32_t m_ibo{0u};
};
} // namespace FIRE

#endif //FIRE_GLVERTEXLAYOUT_H
