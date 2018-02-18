#include "vertexDeclaration.h"

#include <gtest/gtest.h>

TEST(vertexDeclarationTest, DefaultConstructedDeclarationShouldHaveNoSection)
{
    blocks::VertexDeclaration const vDecl;
    ASSERT_TRUE(vDecl.GetSections().empty()); 
}

