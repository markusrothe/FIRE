#include "Utilities.h"
#include <FIRE/Transform.h>
#include <FIRE/Vector.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ostream>

namespace
{
using TestUtil::EXPECT_VEC_EQ;
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

TEST_F(ATransform, SupportsTranslationByIndividualCoordinates)
{
    auto const x = 2.0f;
    auto const y = 3.0f;
    auto const z = -4.0f;
    transform.Translate(x, y, z);
    FIRE::Vector3 const pos{x, y, z};
    EXPECT_EQ(pos, transform.Position());
}

TEST_F(ATransform, SupportsTranslationByAVector)
{
    FIRE::Vector3 const pos{2.0f, 3.0f, -4.0f};
    transform.Translate(pos);
    EXPECT_EQ(pos, transform.Position());
}

TEST_F(ATransform, SupportsScaling)
{
    FIRE::Vector3 const scale{2.0f, 0.0f, 0.0f};
    transform.Scale(scale);
    EXPECT_EQ(scale, transform.GetScaling());
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

TEST_F(ATransform, HasALookAtPoint)
{
    FIRE::Vector3 const defaultLookAt(0.0f, 0.0f, -1.0f);
    EXPECT_EQ(defaultLookAt, transform.LookAt());
}

TEST_F(ATransform, CanChangeItsOrientation)
{
    FIRE::Vector3 const lookAt(0.0f, 1.0f, 0.0f);
    transform.SetLookAt(lookAt);

    EXPECT_VEC_EQ(lookAt, transform.LookAt());
}

TEST_F(ATransform, RotatesProperlyAroundXAxis)
{
    FIRE::Vector3 const xAxis(1.0f, 0.0f, 0.0f);
    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, 1.0f, 0.0f));

    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, 0.0f, 1.0f));

    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, -1.0f, 0.0f));

    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, 0.0f, -1.0f));
}

TEST_F(ATransform, RotatesProperlyAroundYAxis)
{
    FIRE::Vector3 const yAxis(0.0f, 1.0f, 0.0f);
    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(-1.0f, 0.0f, 0.0f));

    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, 0.0f, 1.0f));

    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(1.0f, 0.0f, 0.0f));

    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, 0.0f, -1.0f));
}

TEST_F(ATransform, RotatesProperlyAroundZAxis)
{
    FIRE::Vector3 const zAxis(0.0f, 0.0f, 1.0f);
    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, 0.0f, -1.0f));

    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, 0.0f, -1.0f));

    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, 0.0f, -1.0f));

    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), FIRE::Vector3(0.0f, 0.0f, -1.0f));
}

TEST_F(ATransform, RotationAfterOrientationChange)
{
    transform.SetLookAt(FIRE::Vector3(0.0f, 0.0f, 1.0f));
    transform.Rotate(FIRE::Vector3(0.0f, 1.0f, 0.0f), 90.0f);
    EXPECT_VEC_EQ(FIRE::Vector3(1.0f, 0.0f, 0.0f), transform.LookAt());
}

TEST_F(ATransform, HasARightHandDirection)
{
    EXPECT_VEC_EQ(FIRE::Vector3(1.0f, 0.0f, 0.0f), transform.Right());
}

TEST_F(ATransform, ChangesItsRightHandDirectionBasedOnItsOrientation)
{
    transform.SetLookAt(FIRE::Vector3(1.0f, 0.0f, 0.0f));
    EXPECT_VEC_EQ(FIRE::Vector3(0.0f, 0.0f, 1.0f), transform.Right());
}

TEST_F(ATransform, ChangesItsLookAtPointWhenTranslated)
{
    transform.Translate(1.0f, 1.0f, 1.0f);
    EXPECT_VEC_EQ(FIRE::Vector3(1.0f, 1.0f, 0.0f), transform.LookAt());
}

TEST_F(ATransform, ChangesItsLookAtPointWhenRotatedAfterTranslation)
{
    transform.Translate(1.0f, 1.0f, 1.0f);
    transform.Rotate(transform.Up(), 90.0f);
    EXPECT_VEC_EQ(FIRE::Vector3(0.0f, 1.0f, 1.0f), transform.LookAt());
}
