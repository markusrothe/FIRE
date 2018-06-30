#include "fire/indexData.h"
#include <gtest/gtest.h>

namespace
{
    
} // namespace

TEST(IndexDataTest, DefaultConstructedHasNoIndices)
{
    Fire::IndexData indexData;
    EXPECT_TRUE(indexData.GetIndices().empty());
}
