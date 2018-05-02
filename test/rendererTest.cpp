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
} // namespace 

TEST(Renderer, CanRenderRenderables)
{
    Fire::Renderer renderer;
    std::vector<Fire::Renderable*> renderableVec;
    renderableVec.push_back(&renderable);
    renderer.Render(renderableVec);    
}

