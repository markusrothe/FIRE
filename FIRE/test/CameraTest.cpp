#include <FIRE/Camera.h>
#include <FIRE/Vector.h>
#include <FIRE/Matrix.h>
#include <gtest/gtest.h>

namespace
{
std::string const camName{"cam"};

class ACamera : public ::testing::Test
{
protected:
    FIRE::Camera cam{camName};
};
} // namespace

TEST_F(ACamera, HasAName)
{
    EXPECT_EQ(camName, cam.Name());
}

TEST_F(ACamera, HasADefaultPosition)
{
    EXPECT_EQ(cam.Position(), FIRE::Vector3(0.0f, 0.0f, 0.0f));
}

TEST(Standalone_ACamera, CanBeInitializedWithAPosition)
{
    FIRE::Vector3 const camPos(1.0f, 2.0f, 3.0f);
    FIRE::Camera cam{camName, camPos};
    EXPECT_EQ(camPos, cam.Position());
}

TEST_F(ACamera, CanChangeItsPosition)
{
    FIRE::Vector3 const camPos(1.0f, 2.0f, 3.0f);
    cam.SetPosition(camPos);
    EXPECT_EQ(camPos, cam.Position());
}

TEST_F(ACamera, HasADefaultOrientation)
{
    EXPECT_EQ(cam.Orientation(), FIRE::Vector3(0.0f, 0.0f, 0.0f));
}

TEST(Standalone_ACamera, CanBeInitializedWithAnOrientation)
{
    FIRE::Vector3 const dummyPos(1.0f, 2.0f, 3.0f);
    FIRE::Vector3 const lookAt(3.0f, 2.0f, 1.0f);
    FIRE::Camera cam{camName, dummyPos, lookAt};
    EXPECT_EQ(lookAt, cam.Orientation());
}

TEST_F(ACamera, CanChangeItsOrientation)
{
    FIRE::Vector3 const lookAt(3.0f, 2.0f, 1.0f);
    cam.SetOrientation(lookAt);
    EXPECT_EQ(lookAt, cam.Orientation());
}
