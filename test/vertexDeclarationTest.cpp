#include "vertexDeclaration.h"
#include <algorithm>
#include <gtest/gtest.h>

namespace
{
    class VertexDeclarationTest : public ::testing::Test
    {
    public:
        blocks::VertexDeclaration m_vDecl;
    };

} // namespace

TEST_F(VertexDeclarationTest, DefaultConstructedDeclarationShouldHaveNoSection)
{
    EXPECT_TRUE(m_vDecl.GetSections().empty()); 
}

TEST_F(VertexDeclarationTest, AddingSectionsShouldIncreaseNumberOfSections)
{
    m_vDecl.AddSection("TEST", 2, 0, 3);
    EXPECT_EQ(m_vDecl.GetSections().size(), 1);
}

TEST_F(VertexDeclarationTest, AddedSectionsShouldBeRetrievable)
{
    m_vDecl.AddSection("TEST", 2, 0, 3);

    auto const& vDeclSections = m_vDecl.GetSections();

    auto const foundSectionIt = std::find_if(std::begin(vDeclSections), std::end(vDeclSections)
        , [](auto const& section) { return section.m_attributeName.compare("TEST") == 0; });

    EXPECT_TRUE(std::end(vDeclSections) != foundSectionIt);
}
