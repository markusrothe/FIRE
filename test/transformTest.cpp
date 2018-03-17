#include "transform.h"
#include <gtest/gtest.h>
#include <glm/gtc/matrix_transform.hpp>

namespace
{
    class TransformTest : public ::testing::Test
    {
    public:
        blocks::Transform m_transform;
    };
    
} // namespace

TEST_F(TransformTest, DefaultConstructingShouldInitDefaultValues)
{       
    EXPECT_EQ(m_transform.GetPosition(), glm::vec3(0, 0, 0));
    EXPECT_EQ(m_transform.GetRightVector(), glm::vec3(1, 0, 0));
    EXPECT_EQ(m_transform.GetUpVector(), glm::vec3(0, 1, 0));
    EXPECT_EQ(m_transform.GetForwardVector(), glm::vec3(0, 0, 1));
    EXPECT_EQ(m_transform.GetModelMatrix(), glm::mat4(1.0));
}

TEST_F(TransformTest, TranslatingShouldModifyPosition)
{
    m_transform.Translate(1, 0, 0);
    EXPECT_EQ(m_transform.GetPosition(), glm::vec3(1, 0, 0));

    m_transform.Translate(glm::vec3(0, 2, 0));
    EXPECT_EQ(m_transform.GetPosition(), glm::vec3(1, 2, 0));

    m_transform.Translate(1, 0, -3);
    EXPECT_EQ(m_transform.GetPosition(), glm::vec3(2, 2, -3));
}

TEST_F(TransformTest, TranslationShouldBeContainedInModelMatrix)
{
    glm::vec3 const translation(1, 0, -3);
    m_transform.Translate(translation);
    auto const modelMatrix = m_transform.GetModelMatrix();
    
    EXPECT_EQ(modelMatrix[3], glm::vec4(translation, 1));
}

TEST_F(TransformTest, ScalingShouldBeContainedInModelMatrix)
{
    float const scaleFactor = 2.0f;
    m_transform.Scale(scaleFactor);

    auto const modelMatrix = m_transform.GetModelMatrix();
    auto const scalingMatrix = glm::scale(glm::mat4x4(1.0f), glm::vec3(scaleFactor));
    
    EXPECT_EQ(modelMatrix, scalingMatrix);
}


