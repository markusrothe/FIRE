#include <FIRE/Matrix.h>
#include <gtest/gtest.h>

namespace
{
FIRE::Matrix4x4 const testMatrix({0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f});
} // namespace

TEST(AMatrix, DefaultsToTheIdentityMatrix)
{
    FIRE::Matrix4x4 const mat;
    auto const values = mat.Raw();

    for(auto i = 0u; i < values.size(); ++i)
    {
        EXPECT_EQ(i % 5 == 0u ? 1.0f : 0.0f, values[i]);
    }

    EXPECT_EQ(FIRE::Matrix4x4::identity, mat);
}

TEST(AMatrix, CanBeAccessedVia2DCoordinates)
{
    auto constexpr row = 1;
    auto constexpr column = 1;

    EXPECT_EQ(5.0f, testMatrix.At(row, column));
}

TEST(AMatrix, CanBeMultipliedWithAnotherMatrix)
{
    FIRE::Matrix4x4 const result = testMatrix * testMatrix;
    auto const values = result.Raw();
    EXPECT_EQ(56, values[0]);
    EXPECT_EQ(62, values[1]);
    EXPECT_EQ(68, values[2]);
    EXPECT_EQ(74, values[3]);
    EXPECT_EQ(152, values[4]);
    EXPECT_EQ(174, values[5]);
    EXPECT_EQ(196, values[6]);
    EXPECT_EQ(218, values[7]);
    EXPECT_EQ(248, values[8]);
    EXPECT_EQ(286, values[9]);
    EXPECT_EQ(324, values[10]);
    EXPECT_EQ(362, values[11]);
    EXPECT_EQ(344, values[12]);
    EXPECT_EQ(398, values[13]);
    EXPECT_EQ(452, values[14]);
    EXPECT_EQ(506, values[15]);
}

TEST(AMatrix, CanBeMultipliedAndAssigned)
{
    FIRE::Matrix4x4 result;
    result *= testMatrix;
    EXPECT_EQ(testMatrix, result);
}

TEST(AMatrix, CanBeCopied)
{
    FIRE::Matrix4x4 result(testMatrix);
    EXPECT_EQ(testMatrix, result);
}

TEST(AMatrix, CanBeCopyAssigned)
{
    FIRE::Matrix4x4 result;
    result = testMatrix;
    EXPECT_EQ(testMatrix, result);
}

TEST(AMatrix, CanBeCompared)
{
    FIRE::Matrix4x4 mat;
    EXPECT_NE(mat, testMatrix);
    mat = testMatrix;
    EXPECT_EQ(mat, testMatrix);
}

TEST(AMatrix, CanBeAPerspectiveMatrix)
{
    FIRE::Matrix4x4 view = FIRE::CreatePerspectiveMatrix(10.0f, 10.0f, 10.0f, 10.0f);
}

TEST(AMatrix, CanBeAssignedNewValues)
{
    FIRE::Matrix4x4 mat;
    mat.At(3, 2) = 10.0f;

    EXPECT_EQ(10.0f, mat.At(3, 2));
}
