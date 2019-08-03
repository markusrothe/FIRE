#include "Utilities.h"
#include <FIRE/Transform.h>

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
    glm::vec3 const defaultPosition(0.0f);
    EXPECT_EQ(defaultPosition, transform.Position());
}

TEST_F(ATransform, SupportsTranslationByIndividualCoordinates)
{
    auto const x = 2.0f;
    auto const y = 3.0f;
    auto const z = -4.0f;
    transform.Translate(x, y, z);
    glm::vec3 const pos{x, y, z};
    EXPECT_EQ(pos, transform.Position());
}

TEST_F(ATransform, SupportsTranslationByAVector)
{
    glm::vec3 const pos{2.0f, 3.0f, -4.0f};
    transform.Translate(pos);
    EXPECT_EQ(pos, transform.Position());
}

TEST_F(ATransform, SupportsScaling)
{
    glm::vec3 const scale{2.0f, 0.0f, 0.0f};
    transform.Scale(scale);
    EXPECT_EQ(scale, transform.GetScaling());
}

TEST_F(ATransform, ProvidesAModelMatrix)
{
    glm::mat4x4 const mat(1.0f);
    auto modelMat = transform.ModelMatrix();
    EXPECT_EQ(mat, modelMat);

    transform.Translate(2.0f, 3.0f, -4.0f);
    modelMat = transform.ModelMatrix();

    EXPECT_FLOAT_EQ(2.0f, modelMat[3][0]);
    EXPECT_FLOAT_EQ(3.0f, modelMat[3][1]);
    EXPECT_FLOAT_EQ(-4.0f, modelMat[3][2]);
    EXPECT_FLOAT_EQ(1.0f, modelMat[3][3]);
}

TEST_F(ATransform, HasALookAtPoint)
{
    glm::vec3 const defaultLookAt(0.0f, 0.0f, -1.0f);
    EXPECT_EQ(defaultLookAt, transform.LookAt());
}

TEST_F(ATransform, CanChangeItsOrientation)
{
    glm::vec3 const lookAt(0.0f, 1.0f, 0.0f);
    transform.SetLookAt(lookAt);

    EXPECT_VEC_EQ(lookAt, transform.LookAt());
}

TEST_F(ATransform, RotatesProperlyAroundXAxis)
{
    glm::vec3 const xAxis(1.0f, 0.0f, 0.0f);
    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, 1.0f, 0.0f));

    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, 0.0f, 1.0f));

    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, -1.0f, 0.0f));

    transform.Rotate(xAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, 0.0f, -1.0f));
}

TEST_F(ATransform, RotatesProperlyAroundYAxis)
{
    glm::vec3 const yAxis(0.0f, 1.0f, 0.0f);
    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(-1.0f, 0.0f, 0.0f));

    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, 0.0f, 1.0f));

    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(1.0f, 0.0f, 0.0f));

    transform.Rotate(yAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, 0.0f, -1.0f));
}

TEST_F(ATransform, RotatesProperlyAroundZAxis)
{
    glm::vec3 const zAxis(0.0f, 0.0f, 1.0f);
    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, 0.0f, -1.0f));

    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, 0.0f, -1.0f));

    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, 0.0f, -1.0f));

    transform.Rotate(zAxis, 90.0f);
    EXPECT_VEC_EQ(transform.LookAt(), glm::vec3(0.0f, 0.0f, -1.0f));
}

TEST_F(ATransform, RotationAfterOrientationChange)
{
    transform.SetLookAt(glm::vec3(0.0f, 0.0f, 1.0f));
    transform.Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
    EXPECT_VEC_EQ(glm::vec3(1.0f, 0.0f, 0.0f), transform.LookAt());
}

TEST_F(ATransform, HasARightHandDirection)
{
    EXPECT_VEC_EQ(glm::vec3(1.0f, 0.0f, 0.0f), transform.Right());
}

TEST_F(ATransform, ChangesItsRightHandDirectionBasedOnItsOrientation)
{
    transform.SetLookAt(glm::vec3(1.0f, 0.0f, 0.0f));
    EXPECT_VEC_EQ(glm::vec3(0.0f, 0.0f, 1.0f), transform.Right());
}

TEST_F(ATransform, ChangesItsLookAtPointWhenTranslated)
{
    transform.Translate(1.0f, 1.0f, 1.0f);
    EXPECT_VEC_EQ(glm::vec3(1.0f, 1.0f, 0.0f), transform.LookAt());
}

TEST_F(ATransform, ChangesItsLookAtPointWhenRotatedAfterTranslation)
{
    transform.Translate(1.0f, 1.0f, 1.0f);
    transform.Rotate(transform.Up(), 90.0f);
    EXPECT_VEC_EQ(glm::vec3(0.0f, 1.0f, 1.0f), transform.LookAt());
}

TEST_F(ATransform, DescribesLinearAcceleration)
{
    glm::vec3 const acceleration{1.0f, 2.0f, 3.0f};
    transform.Accelerate(acceleration);
    EXPECT_VEC_EQ(acceleration, transform.Acceleration());
    transform.Accelerate({0.0f, -1.0f, 0.0f});
    EXPECT_VEC_EQ(glm::vec3(1.0f, 1.0f, 3.0f), transform.Acceleration());
}
