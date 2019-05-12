#include <FIRE/Transform.h>
#include <FIRE/Vector.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ostream>

namespace
{
class ATransform : public ::testing::Test
{
public:
    void EXPECT_VEC_EQ(
        FIRE::Vector3 const& expected, FIRE::Vector3 const& actual)
    {
        auto const eps = 0.000001f;
        EXPECT_THAT(actual.x, ::testing::FloatNear(expected.x, eps));
        EXPECT_THAT(actual.y, ::testing::FloatNear(expected.y, eps));
        EXPECT_THAT(actual.z, ::testing::FloatNear(expected.z, eps));
    }

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

TEST_F(ATransform, CanChangeItsOrientation)
{
    FIRE::Vector3 const lookAt(3.0f, 2.0f, 1.0f);
    transform.SetOrientation(lookAt);

    EXPECT_VEC_EQ(lookAt, transform.Orientation());
}

TEST_F(ATransform, RotatesProperlyAroundXAxis)
{
    FIRE::Vector3 const xAxis(1.0f, 0.0f, 0.0f);
    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, 1.0f, 0.0f));

    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, 0.0f, 1.0f));

    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, -1.0f, 0.0f));

    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, 0.0f, -1.0f));
}

TEST_F(ATransform, RotatesProperlyAroundYAxis)
{
    FIRE::Vector3 const yAxis(0.0f, 1.0f, 0.0f);
    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(-1.0f, 0.0f, 0.0f));

    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, 0.0f, 1.0f));

    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(1.0f, 0.0f, 0.0f));

    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, 0.0f, -1.0f));
}

TEST_F(ATransform, RotatesProperlyAroundZAxis)
{
    FIRE::Vector3 const zAxis(0.0f, 0.0f, 1.0f);
    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, 0.0f, -1.0f));

    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, 0.0f, -1.0f));

    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, 0.0f, -1.0f));

    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.Orientation(), FIRE::Vector3(0.0f, 0.0f, -1.0f));
}

TEST_F(ATransform, RotationAfterOrientationChange)
{
    transform.SetOrientation(FIRE::Vector3(1.0f, 0.0f, 1.0f));
    transform.Rotate(FIRE::Vector3(0.0f, 1.0f, 0.0f), 90.0f);
    EXPECT_VEC_EQ(FIRE::Vector3(1.0f, 0.0f, -1.0f), transform.Orientation());
}
