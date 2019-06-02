#include <FIRE/Camera.h>
#include <FIRE/Matrix.h>
#include <FIRE/Vector.h>
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
    EXPECT_EQ(cam.GetTransform().Position(), FIRE::Vector3(0.0f, 0.0f, 0.0f));
}

TEST(Standalone_ACamera, CanBeInitializedWithAPosition)
{
    FIRE::Vector3 const camPos(1.0f, 2.0f, 3.0f);
    FIRE::Camera cam{camName, camPos};
    EXPECT_EQ(camPos, cam.GetTransform().Position());
}

TEST(Standalone_ACamera, CanBeInitializedWithAnOrientation)
{
    FIRE::Vector3 const dummyPos(1.0f, 2.0f, 3.0f);
    FIRE::Vector3 const viewDir(0.0f, 0.0f, 1.0f);
    FIRE::Camera cam{camName, dummyPos, viewDir};
    EXPECT_EQ(viewDir, cam.GetTransform().Orientation());
}
