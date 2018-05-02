#include "fire/renderable.h"
#include "fire/vertexData.h"
#include "fire/vertexDeclaration.h"
#include <gtest/gtest.h>
#include <string>

namespace
{
    std::string const renderableName;
    Fire::VertexData const vertexData;
    Fire::VertexDeclaration vertexDeclaration;
    std::string const sectionName = "vertex";
    unsigned int const sectionSize = 2;
    unsigned int const sectionOffset = 3;
    unsigned int const sectionStride = 4;

    Fire::Renderable CreateTestRenderable()
    {               
        vertexDeclaration.AddSection(
            sectionName, sectionSize, sectionStride, sectionOffset);
        
        return Fire::Renderable(renderableName, vertexData, vertexDeclaration);
    }        
    
    class RenderableTest : public ::testing::Test
    {
    public:
        RenderableTest()
            : m_renderable(CreateTestRenderable())
            {

            }
        
        Fire::Renderable m_renderable;
    };
    
} // namespace

TEST_F(RenderableTest, RenderablesHaveAName)
{
    EXPECT_EQ(m_renderable.GetName(), renderableName);
}

TEST_F(RenderableTest, RenderablesContainTheirVertexDeclaration)
{
    auto const& vDecl = m_renderable.GetVertexDeclaration();
    auto const sectionIter = vDecl.GetSection(sectionName);
    
    ASSERT_TRUE(sectionIter != std::end(vDecl.GetSections()));
    
    EXPECT_EQ(sectionIter->m_offset, sectionOffset);
}

TEST(RenderableTestStandalone, RenderablesAreConstructedFromVertexData)
{
    Fire::Renderable(renderableName, vertexData, vertexDeclaration);
}


/**
   CanBeMarkedForReupload
   ContainReferencesToTextures
   ContainReferencesToMaterials
   ContainRenderingMetaInfo
   CreateVertexBuffer
   CreateIndexBuffer
   CreateVertexArrayObjects
*/
