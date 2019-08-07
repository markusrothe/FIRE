#include "FontLoader.h"
#include "TextureFactoryMock.h"
#include <FIRE/TextureManager.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace FIRE_tests
{
class FontLoaderMock : public FIRE::FontLoader
{
public:
    MOCK_METHOD1(LoadChar, FIRE::FontCharacter(char));
};
} // namespace FIRE_tests

namespace
{
using ::testing::_;
using ::testing::Return;

class ATextureManager : public ::testing::Test
{
protected:
    FIRE::TextureManager CreateTextureManager()
    {
        return FIRE::TextureManager(std::move(texFactory), std::move(fontLoader));
    }

    std::unique_ptr<FIRE_tests::TextureFactoryMock> texFactory{std::make_unique<FIRE_tests::TextureFactoryMock>()};
    std::unique_ptr<FIRE_tests::FontLoaderMock> fontLoader{std::make_unique<FIRE_tests::FontLoaderMock>()};
    uint32_t width{10};
    uint32_t height{10};
    std::vector<uint8_t> data{0, 1, 2, 3};
};

} // namespace

TEST_F(ATextureManager, CreatesFontCharacters)
{
    EXPECT_CALL(*fontLoader, LoadChar('A'))
        .WillOnce(Return(::testing::ByMove(FIRE::FontCharacter(nullptr, {width, height}, {10, 10}, 10, data))));

    EXPECT_CALL(*texFactory, Create2DTexture(width, height, data, _, _, _));

    auto texManager = CreateTextureManager();
    texManager.CreateFontCharTexture('A');
}

TEST_F(ATextureManager, CreatesImageTextures)
{
    uint8_t numComponents = 2;
    auto wrappingMode = FIRE::Texture2D::WrappingMode::WRAP;
    auto filter = FIRE::Texture2D::Filter::NEAREST;

    EXPECT_CALL(*texFactory, Create2DTexture(width, height, data, numComponents, wrappingMode, filter));

    auto texManager = CreateTextureManager();

    texManager.CreateImageTexture("tex", width, height, data, numComponents, wrappingMode, filter);
}
