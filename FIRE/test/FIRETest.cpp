#include <gtest/gtest.h>
#include <FIRE/FIRE.h>

TEST(FIRETest, Hello_FIRE_Test)
{
	FIRE::HelloWorld();  
	EXPECT_TRUE(true);   
}

TEST(FIRETest, Hello_2nd_FIRE_Test)
{
    FIRE::HelloWorld();
    EXPECT_TRUE(true);
} 