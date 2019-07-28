#include "TextureFactory.h"
#include "FontTextureFactory.h"
#include "ImageTextureFactory.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace
{
using ::testing::Return;
class FontTextureFactoryMock : public FIRE::FontTextureFactory
{
public:
    MOCK_METHOD1(CreateTexture, FIRE::FontCharacter*(char));
};

class ImageTextureFactoryMock : public FIRE::ImageTextureFactory
{
public:
    MOCK_METHOD3(CreateTexture, FIRE::Texture(uint32_t, uint32_t, std::vector<uint8_t>));
};

class ATextureFactory : public ::testing::Test
{
protected:
    FIRE::TextureFactory CreateTextureFactory()
    {
        return FIRE::TextureFactory(std::move(imageTexFactory), std::move(fontFactory));
    }

    std::unique_ptr<FontTextureFactoryMock> fontFactory{std::make_unique<FontTextureFactoryMock>()};
    std::unique_ptr<ImageTextureFactoryMock> imageTexFactory{std::make_unique<ImageTextureFactoryMock>()};
};

} // namespace

TEST_F(ATextureFactory, CreatesFontCharacters)
{
    EXPECT_CALL(*fontFactory, CreateTexture('A'));
    auto texFactory = CreateTextureFactory();
    texFactory.CreateFontCharTexture('A');
}

TEST_F(ATextureFactory, CreatesImageTextures)
{
    std::vector<uint8_t> const data = {0, 1, 2, 3};
    EXPECT_CALL(*imageTexFactory, CreateTexture(100, 120, data));

    auto texFactory = CreateTextureFactory();
    texFactory.CreateImageTexture(100, 120, data);
}