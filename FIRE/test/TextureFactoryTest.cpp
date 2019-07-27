#include "TextureFactory.h"
#include "FontTextureFactory.h"
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
} // namespace

TEST(ATextureFactory, CreatesFontCharacters)
{
    auto fontFactory = std::make_unique<FontTextureFactoryMock>();
    EXPECT_CALL(*fontFactory, CreateTexture('A'));

    FIRE::TextureFactory texFactory(std::move(fontFactory));
    texFactory.CreateFontCharTexture('A');
}