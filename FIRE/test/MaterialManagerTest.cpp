#include <gtest/gtest.h>

#include "MaterialManager.h"
#include "ShaderFactory.h"

namespace
{
class ShaderFactoryStub : public FIRE::ShaderFactory
{
public:
    unsigned int CreateDefaultShader()
    {
        return 42;
    }
};
} // namespace

TEST(AMaterialManager, StartsWithADefaultMaterial)
{
    auto shaderFactory = std::make_unique<ShaderFactoryStub>();
    FIRE::MaterialManager materialManager(std::move(shaderFactory));

    EXPECT_EQ(42u, materialManager.GetShader("Default"));
}
