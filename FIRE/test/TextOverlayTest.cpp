#include <FIRE/TextOverlay.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

TEST(ATextOverlay, CanBeCompared)
{
    FIRE::TextOverlay lhs("text", 0.5f, 0.5f, 1.3f);
    FIRE::TextOverlay rhs("tab", 0.1f, 0.2f, 0.3f);
    EXPECT_NE(lhs, rhs);

    rhs.x = lhs.x;
    EXPECT_NE(lhs, rhs);

    rhs.y = lhs.y;
    EXPECT_NE(lhs, rhs);

    rhs.scale = lhs.scale;
    EXPECT_NE(lhs, rhs);

    rhs.text = lhs.text;
    EXPECT_EQ(lhs, rhs);
}