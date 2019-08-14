#ifndef FIRE_VERTEXLAYOUTSTUB_H
#define FIRE_VERTEXLAYOUTSTUB_H
#include "VertexLayout.h"
namespace FIRE_tests
{
class VertexLayoutStub : public FIRE::VertexLayout
{
public:
    VertexLayoutStub()
        : FIRE::VertexLayout(FIRE::DrawMode::INDEXED)
    {
    }
    void BindLayout() override
    {
    }
    void ReleaseLayout() override
    {
    }
    void BufferData(uint32_t, void*) override
    {
    }
    void BufferIndexData(uint32_t, void*) override
    {
    }
    void BufferSubData(uint32_t, uint32_t, void*) override
    {
    }
    void AddVertexAttribute(uint32_t, uint32_t, uint32_t) override
    {
    }
};
} // namespace FIRE_tests
#endif //FIRE_VERTEXLAYOUTSTUB_H
