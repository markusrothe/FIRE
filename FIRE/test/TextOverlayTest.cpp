#include <FIRE/TextOverlay.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

TEST(ATextOverlay, HasAPosition)
{
    float const x = 0.5f;
    float const y = 0.3f;
    FIRE::TextOverlay textOverlay("", x, y);
    EXPECT_EQ(x, textOverlay.x());
    EXPECT_EQ(y, textOverlay.y());
}

TEST(ATextOverlay, HasAText)
{
    std::string const text("text");
    FIRE::TextOverlay textOverlay(text, 0.5f, 0.5f);
    EXPECT_EQ(text, textOverlay.GetText());
}