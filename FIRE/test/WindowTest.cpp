#include <FIRE/RenderContext.h>
#include <FIRE/Window.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>

namespace FIRE
{

class RenderContextMock : public RenderContext
{
public:
    ~RenderContextMock() override = default;
    MOCK_METHOD0(SwapBuffers, void(void));
};
} // namespace FIRE

namespace
{
constexpr auto title{"WindowTitle"};
constexpr auto width{200u};
constexpr auto height{400u};

class WindowTest : public ::testing::Test
{
public:
    FIRE::Window window{title, width, height};
};

} // namespace

TEST_F(WindowTest, HasATitle) { EXPECT_EQ(title, window.GetTitle()); }

TEST_F(WindowTest, HasAWidth) { EXPECT_EQ(width, window.GetWidth()); }

TEST_F(WindowTest, HasAHeight) { EXPECT_EQ(height, window.GetHeight()); }

TEST_F(WindowTest, IsResizable)
{
    window.Resize(150, 300);
    EXPECT_EQ(150, window.GetWidth());
    EXPECT_EQ(300, window.GetHeight());
}

TEST_F(WindowTest, CanBeClosed)
{
    EXPECT_FALSE(window.ShouldClose());
    window.Close();
    EXPECT_TRUE(window.ShouldClose());
}

TEST_F(WindowTest, SupportsDoubleBuffering)
{
    auto context = std::make_unique<FIRE::RenderContextMock>();
    EXPECT_CALL(*context, SwapBuffers());
    window.SetRenderContext(std::move(context));

    window.SwapBuffers();
}
