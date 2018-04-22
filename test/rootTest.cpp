#include "fire/root.h"

#include <gtest/gtest.h>

namespace
{
    auto const windowWidth = 1200;
    auto const windowHeight = 800;
    
} // namespace

TEST(RootTest, RootExistsOnlyOnce)
{
    Fire::RootFactory& rootFactory = Fire::RootFactory::GetInstance();
    
    Fire::Root& root = rootFactory.GetRoot("name", windowWidth, windowHeight);
    Fire::Root& otherRoot = rootFactory.GetRoot("other", windowWidth, windowHeight);
    
    ASSERT_EQ(&root, &otherRoot);
}

TEST(RootTest, CreatingRootCreatesAWindow)
{
    
}


