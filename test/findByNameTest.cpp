#include "fire/findByName.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>

namespace
{
    std::vector<int> const vec = {1, 2, 3};
    std::string const ONE = "one";

    std::string GetName(int i)
    {
        return i == 1 ? ONE : "";
    }
    
} // namespace


TEST(FindByNameTest, ReturnsCollectionEntryIfFound)
{
    auto foundValue = Fire::FindByName(vec, ONE, GetName);
    EXPECT_EQ(foundValue, 1);
}

TEST(FindByNameTest, ReturnsDefaultConstructedEntryIfNotFound)
{
    auto foundValue = Fire::FindByName(vec, "four", GetName);
    EXPECT_EQ(foundValue, 0);
}
