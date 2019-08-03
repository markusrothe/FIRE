#include "TextureManager.h"
#include "TextureFactoryMock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
using ::testing::_;
using ::testing::Return;

class ATextureManager : public ::testing::Test
{
protected:
    FIRE::TextureManager CreateTextureManager()
    {
        return FIRE::TextureManager(std::move(texFactory));
    }

    std::unique_ptr<FIRE_tests::TextureFactoryMock> texFactory{std::make_unique<FIRE_tests::TextureFactoryMock>()};
};

} // namespace

TEST_F(ATextureManager, DISABLED_CreatesFontCharacters)
{
    EXPECT_CALL(*texFactory, Create2DTexture(_, _, _));
    auto texManager = CreateTextureManager();
    texManager.CreateFontCharTexture('A');
}

TEST_F(ATextureManager, CreatesImageTextures)
{
    std::vector<uint8_t> data = {0, 1, 2, 3};
    EXPECT_CALL(*texFactory, Create2DTexture(100, 120, data));

    auto texManager = CreateTextureManager();
    texManager.CreateImageTexture(100, 120, data);
}