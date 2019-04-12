#include <FIRE/Camera.h>
#include <FIRE/Vertex.h>
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
    EXPECT_EQ(cam.Position(), FIRE::Vertex(0.0f, 0.0f, 0.0f));
}

TEST(Standalone_ACamera, CanBeInitializedWithAPosition)
{
    FIRE::Vertex const camPos(1.0f, 2.0f, 3.0f);
    FIRE::Camera cam{camName, camPos};
    EXPECT_EQ(camPos, cam.Position());
}

TEST_F(ACamera, CanChangeItsPosition)
{
    FIRE::Vertex const camPos(1.0f, 2.0f, 3.0f);
    cam.SetPosition(camPos);
    EXPECT_EQ(camPos, cam.Position());
}

TEST_F(ACamera, HasADefaultOrientation)
{
    EXPECT_EQ(cam.Orientation(), FIRE::Vertex(0.0f, 0.0f, 0.0f));
}

TEST(Standalone_ACamera, CanBeInitializedWithAnOrientation)
{
    FIRE::Vertex const dummyPos(1.0f, 2.0f, 3.0f);
    FIRE::Vertex const lookAt(3.0f, 2.0f, 1.0f);
    FIRE::Camera cam{camName, dummyPos, lookAt};
    EXPECT_EQ(lookAt, cam.Orientation());
}

TEST_F(ACamera, CanChangeItsOrientation)
{
    FIRE::Vertex const lookAt(3.0f, 2.0f, 1.0f);
    cam.SetOrientation(lookAt);
    EXPECT_EQ(lookAt, cam.Orientation());
}
