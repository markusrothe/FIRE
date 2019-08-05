#ifndef FIRE_TEST_Utilities_h
#define FIRE_TEST_Utilities_h

#include <FIRE/glmfwd.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace TestUtil
{
inline void EXPECT_VEC_EQ(glm::vec3 const& expected, glm::vec3 const& actual)
{
    auto const eps = 0.000001f;
    EXPECT_THAT(actual.x, ::testing::FloatNear(expected.x, eps));
    EXPECT_THAT(actual.y, ::testing::FloatNear(expected.y, eps));
    EXPECT_THAT(actual.z, ::testing::FloatNear(expected.z, eps));
}
} // namespace TestUtil

#endif // FIRE_TEST_Utilities_h
