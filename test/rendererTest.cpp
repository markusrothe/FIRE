#include "fire/renderer.h"
#include "fire/vertexData.h"
#include "fire/vertexDeclaration.h"
#include "fire/renderable.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

namespace
{
    Fire::VertexData vertexData;
    Fire::VertexDeclaration vertexDecl;
    Fire::Renderable renderable("name", vertexData, vertexDecl);

    class RendererTest : public ::testing::Test
    {
    public:

        Fire::Renderer m_renderer;
    };
    
} // namespace 

TEST_F(RendererTest, RendererCanRenderRenderables)
{
    std::vector<Fire::Renderable*> renderableVec;
    renderableVec.push_back(&renderable);
    m_renderer.Render(renderableVec);    
}



