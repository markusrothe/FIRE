#include <FIRE/Renderable.h>
#include <gtest/gtest.h>

TEST(ARenderable, IsOnlyComparedViaItsName)
{
    std::string const NAME{"name"};
    FIRE::Renderable r0, r1;
    r0.name = NAME;
    r1.name = NAME;
    EXPECT_EQ(r0, r1);

    r0.name = "another name";
    EXPECT_NE(r0, r1);
    EXPECT_LT(r0, r1);
}