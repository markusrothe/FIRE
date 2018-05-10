#include "fire/renderable.h"
#include "fire/vertexDeclaration.h"
#include "fire/vertexData.h"
#include <gtest/gtest.h>
#include <string>

namespace
{
    std::string const NAME("name");

    class RenderableTest : public ::testing::Test
    {
    public:
        RenderableTest() : m_renderable(NAME) {}

        void SetVertexDeclarationWithSection(Fire::VertexDeclarationSection const& section)
        {
            Fire::VertexDeclaration vDecl;
            vDecl.AddSection(section.m_attributeName, section.m_numElements, section.m_stride, section.m_offset);
            m_renderable.SetVertexDeclaration(vDecl);
        }

    protected:
        Fire::Renderable m_renderable;
    };    
} // namespace

namespace Fire
{
    bool operator==(Fire::VertexDeclarationSection const& lhs, Fire::VertexDeclarationSection const& rhs)
    {
        return lhs.m_attributeName.compare(rhs.m_attributeName) == 0 &&
            lhs.m_numElements == rhs.m_numElements &&
            lhs.m_offset == rhs.m_offset &&
            lhs.m_stride == rhs.m_stride;
    }
} // namespace Fire


TEST_F(RenderableTest, RenderablesHaveAName)
{
    EXPECT_EQ(m_renderable.GetName(), NAME);
}

TEST_F(RenderableTest, AVertexDeclarationCanBeSetInRenderables)
{
    auto const attributeName("attr");
    Fire::VertexDeclarationSection const section(attributeName, 4, 3, 2);
    
    SetVertexDeclarationWithSection(section);

    EXPECT_EQ(m_renderable.GetVertexDeclaration().GetSection(attributeName), section);
}

TEST_F(RenderableTest, SettingAVertexDeclarationOverridesThePreviousOne)
{
    auto const attributeName("attr");    
    Fire::VertexDeclarationSection const section(attributeName, 4, 3, 2);
    
    auto const attributeNameOther("other");
    Fire::VertexDeclarationSection const otherSection(attributeNameOther, 9, 21, 5);
    
    SetVertexDeclarationWithSection(section);
    SetVertexDeclarationWithSection(otherSection);

    EXPECT_EQ(m_renderable.GetVertexDeclaration().GetSection(attributeNameOther), otherSection);
}

TEST_F(RenderableTest, RenderablesHaveVertexData)
{
    EXPECT_NE(&m_renderable.GetVertexData(), nullptr);
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
