#include <FIRE/Transform.h>
#include <gtest/gtest.h>

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

    EXPECT_EQ(2.0f, modelMat.At(3, 0));
    EXPECT_EQ(3.0f, modelMat.At(3, 1));
    EXPECT_EQ(-4.0f, modelMat.At(3, 2));
    EXPECT_EQ(1.0f, modelMat.At(3, 3));
}
