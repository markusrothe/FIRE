#include <FIRE/Transform.h>
#include <FIRE/Vector.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ostream>

namespace FIRE
{
std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
    os << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
    return os;
}
} // namespace FIRE

namespace
{
class ATransform : public ::testing::Test
{
public:
    FIRE::Transform transform;
};
} // namespace

TEST_F(ATransform, DescribesAPosition)
{
    FIRE::Vector3 const defaultPosition;
    EXPECT_EQ(defaultPosition, transform.Position());
}

TEST_F(ATransform, SupportsTranslation)
{
    auto const x = 2.0f;
    auto const y = 3.0f;
    auto const z = -4.0f;
    transform.Translate(x, y, z);
    FIRE::Vector3 const pos{x, y, z};
    EXPECT_EQ(pos, transform.Position());
}

TEST_F(ATransform, ProvidesAModelMatrix)
{
    FIRE::Matrix4x4 const mat;
    auto modelMat = transform.ModelMatrix();
    EXPECT_EQ(mat, modelMat);

    transform.Translate(2.0f, 3.0f, -4.0f);
    modelMat = transform.ModelMatrix();

    EXPECT_FLOAT_EQ(2.0f, modelMat.At(3, 0));
    EXPECT_FLOAT_EQ(3.0f, modelMat.At(3, 1));
    EXPECT_FLOAT_EQ(-4.0f, modelMat.At(3, 2));
    EXPECT_FLOAT_EQ(1.0f, modelMat.At(3, 3));
}

TEST_F(ATransform, DescribesAnOrientation)
{
    FIRE::Vector3 const defaultOrientation(0.0f, 0.0f, -1.0f);
    EXPECT_EQ(defaultOrientation, transform.Orientation());
}

TEST_F(ATransform, SupportsRotationAroundAxisInDegrees)
{
    transform.Rotate(FIRE::Vector3(0.0f, 1.0f, 0.0f), 90.0f);
    auto orientation = transform.Orientation();

    auto eps = 0.000001f;
    EXPECT_THAT(orientation.x, ::testing::FloatNear(-1.0f, eps));
    EXPECT_THAT(orientation.y, ::testing::FloatNear(0.0f, eps));
    EXPECT_THAT(orientation.z, ::testing::FloatNear(0.0f, eps));

    transform.Rotate(FIRE::Vector3(0.0f, 0.0f, 1.0f), 90.0f);
    orientation = transform.Orientation();
    EXPECT_THAT(orientation.x, ::testing::FloatNear(0.0f, eps));
    EXPECT_THAT(orientation.y, ::testing::FloatNear(-1.0f, eps));
    EXPECT_THAT(orientation.z, ::testing::FloatNear(0.0f, eps));
}
