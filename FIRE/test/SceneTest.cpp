#include <FIRE/Scene.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{

class AScene : public ::testing::Test
{
public:
    FIRE::Scene scene;
};

} // namespace
