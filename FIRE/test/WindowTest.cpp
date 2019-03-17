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
    MOCK_METHOD0(PollEvents, void(void));
    MOCK_METHOD0(ShouldClose, bool());
    MOCK_METHOD0(Close, void(void));
    MOCK_METHOD2(Resize, void(unsigned int width, unsigned int height));
};
} // namespace FIRE

namespace
{
using ::testing::Return;
constexpr auto title{"WindowTitle"};
constexpr auto width{200u};
constexpr auto height{400u};

class WindowTest : public ::testing::Test
{
public:
    WindowTest()
        : context(std::make_unique<FIRE::RenderContextMock>())
    {
    }
    FIRE::Window window{title, width, height};
    std::unique_ptr<FIRE::RenderContextMock> context;
};

} // namespace

TEST_F(WindowTest, HasATitle)
{
    EXPECT_EQ(title, window.GetTitle());
}

TEST_F(WindowTest, HasAWidth)
{
    EXPECT_EQ(width, window.GetWidth());
}

TEST_F(WindowTest, HasAHeight)
{
    EXPECT_EQ(height, window.GetHeight());
}

TEST_F(WindowTest, IsResizable)
{
    EXPECT_CALL(*context, Resize(150u, 300u));
    window.SetRenderContext(std::move(context));

    window.Resize(150u, 300u);
    EXPECT_EQ(150u, window.GetWidth());
    EXPECT_EQ(300u, window.GetHeight());
}

TEST_F(WindowTest, CanBeClosed)
{
    EXPECT_CALL(*context, ShouldClose())
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    window.SetRenderContext(std::move(context));

    EXPECT_FALSE(window.ShouldClose());
    window.Close();
    EXPECT_TRUE(window.ShouldClose());
}

TEST_F(WindowTest, ForwardsClosingToRenderContext)
{
    EXPECT_CALL(*context, Close());
    window.SetRenderContext(std::move(context));
    window.Close();
}

TEST_F(WindowTest, ForwardsClosedCheckToRenderContext)
{
    EXPECT_CALL(*context, ShouldClose());
    window.SetRenderContext(std::move(context));
    window.ShouldClose();
}

TEST_F(WindowTest, SupportsDoubleBuffering)
{
    EXPECT_CALL(*context, SwapBuffers());
    window.SetRenderContext(std::move(context));
    window.SwapBuffers();
}

TEST_F(WindowTest, CanBePolledForEvents)
{
    EXPECT_CALL(*context, PollEvents());
    window.SetRenderContext(std::move(context));
    window.PollEvents();
}
