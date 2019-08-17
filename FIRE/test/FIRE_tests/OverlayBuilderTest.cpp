#include "ShaderFactoryMock.h"
#include "Texture2DStub.h"
#include "TextureFactoryMock.h"
#include <FIRE/AssetFacade.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
using namespace testing;
namespace
{
class AnOverlayBuilder : public Test
{
public:
    AnOverlayBuilder()
        : textureFactory{std::make_unique<FIRE_tests::TextureFactoryMock>()}
        , textureFactoryMock{*textureFactory}
        , shaderFactory{std::make_unique<FIRE_tests::ShaderFactoryMock>()}
        , shaderFactoryMock{*shaderFactory}
        , assets(std::move(textureFactory), std::move(shaderFactory))
    {
    }

    std::unique_ptr<FIRE_tests::TextureFactoryMock> textureFactory;
    FIRE_tests::TextureFactoryMock& textureFactoryMock;

    std::unique_ptr<FIRE_tests::ShaderFactoryMock> shaderFactory;
    FIRE_tests::ShaderFactoryMock& shaderFactoryMock;

    FIRE::AssetFacade assets;
    std::string NAME{"name"};
};
} // namespace

TEST_F(AnOverlayBuilder, CreatesTextOverlays)
{
    auto const textOverlays = assets.CreateTextOverlays(NAME, 1u)
                                  .WithText("overlay_text")
                                  .Build();

    ASSERT_THAT(textOverlays, SizeIs(1u));
    ASSERT_THAT(textOverlays[0].name, Eq(NAME + "0"));
    ASSERT_THAT(textOverlays[0].text, Eq("overlay_text"));
    ASSERT_THAT(textOverlays[0].x, FloatEq(0.0f));
    ASSERT_THAT(textOverlays[0].y, FloatEq(0.0f));
}

TEST_F(AnOverlayBuilder, CreatesMultipleOverlays)
{
    auto const textOverlays = assets.CreateTextOverlays(NAME, 2u)
                                  .WithText("text0")
                                  .WithText("text1")
                                  .Build();

    ASSERT_THAT(textOverlays, SizeIs(2u));
    ASSERT_THAT(textOverlays[0].name, Eq(NAME + "0"));
    ASSERT_THAT(textOverlays[0].text, Eq("text0"));
    ASSERT_THAT(textOverlays[1].name, Eq(NAME + "1"));
    ASSERT_THAT(textOverlays[1].text, Eq("text1"));
}

TEST_F(AnOverlayBuilder, ThrowsIfMoreTextThanOverlaysWereSpecified)
{
    ASSERT_ANY_THROW(assets.CreateTextOverlays(NAME, 1u)
                         .WithText("text0")
                         .WithText("text1")
                         .Build());
}

TEST_F(AnOverlayBuilder, CreatesTextOverlaysAtSpecificPositions)
{
    auto const textOverlays = assets.CreateTextOverlays(NAME, 1u)
                                  .At(0.5f, 0.7f)
                                  .Build();
    ASSERT_THAT(textOverlays[0].x, FloatEq(0.5f));
    ASSERT_THAT(textOverlays[0].y, FloatEq(0.7f));
}

TEST_F(AnOverlayBuilder, CreatesMultipleTextOverlaysAtDifferentPositions)
{
    auto const textOverlays = assets.CreateTextOverlays(NAME, 2u)
                                  .At(0.1f, 0.2f)
                                  .At(0.3f, 0.4f)
                                  .Build();

    ASSERT_THAT(textOverlays[0].x, FloatEq(0.1f));
    ASSERT_THAT(textOverlays[0].y, FloatEq(0.2f));
    ASSERT_THAT(textOverlays[1].x, FloatEq(0.3f));
    ASSERT_THAT(textOverlays[1].y, FloatEq(0.4f));
}

TEST_F(AnOverlayBuilder, ThrowsIfMorePositionsThanOverlaysWereSpecified)
{
    ASSERT_ANY_THROW(assets.CreateTextOverlays(NAME, 1u)
                         .At(0.1f, 0.2f)
                         .At(0.3f, 0.4f)
                         .Build());
}

TEST_F(AnOverlayBuilder, CreatesTextOverlaysThatCanBeScaled)
{
    auto const textOverlays = assets.CreateTextOverlays(NAME, 1u)
                                  .ScaledBy(2.0f)
                                  .Build();

    ASSERT_THAT(textOverlays[0].scale, FloatEq(2.0f));
}

TEST_F(AnOverlayBuilder, ThrowsIfMoreScalingsThanOverlaysWereSpecified)
{
    ASSERT_ANY_THROW(assets.CreateTextOverlays(NAME, 1u)
                         .ScaledBy(0.1f)
                         .ScaledBy(0.3f)
                         .Build());
}

TEST_F(AnOverlayBuilder, CreatesMultipleTextOverlaysWithDifferentScalings)
{
    auto const textOverlays = assets.CreateTextOverlays(NAME, 2u)
                                  .ScaledBy(0.1f)
                                  .ScaledBy(0.3f)
                                  .Build();

    ASSERT_THAT(textOverlays[0].scale, FloatEq(0.1f));
    ASSERT_THAT(textOverlays[1].scale, FloatEq(0.3f));
}

TEST_F(AnOverlayBuilder, CreatesTextOverlaysWithTheDefaultTextMaterial)
{
    auto const textOverlays = assets.CreateTextOverlays(NAME, 1u)
                                  .Build();

    ASSERT_THAT(textOverlays[0].material.Name(), Eq("TextDefault"));
}