#include "fire/indexData.h"
#include <gtest/gtest.h>

namespace
{
class IndexDataTest : public ::testing::Test
{
public:
    IndexDataTest()
        : m_indexData()
    {
    }

protected:
    Fire::IndexData m_indexData;
};
} // namespace

TEST_F(IndexDataTest, DefaultConstructedHasNoIndices)
{
    EXPECT_TRUE(m_indexData.GetIndices().empty());
}

TEST_F(IndexDataTest, IndicesCanBeAddedOneAtATime)
{
    m_indexData.AddIndex(2u);

    ASSERT_EQ(m_indexData.GetIndices().size(), 1);
    EXPECT_EQ(m_indexData.GetIndices()[0], 2);
}

TEST_F(IndexDataTest, MultipleIndicesCanBeAddedAtOnce)
{
    m_indexData.AddIndices({0, 1, 2});

    ASSERT_EQ(m_indexData.GetIndices().size(), 3);
    EXPECT_EQ(m_indexData.GetIndices()[0], 0);
    EXPECT_EQ(m_indexData.GetIndices()[1], 1);
    EXPECT_EQ(m_indexData.GetIndices()[2], 2);
}
