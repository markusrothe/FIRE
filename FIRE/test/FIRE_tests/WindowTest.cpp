#include <FIRE/InputListener.h>
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
    MOCK_METHOD1(RegisterInputListener, void(InputListener*));
    MOCK_METHOD0(CaptureCursor, void(void));
    MOCK_METHOD0(ReleaseCursor, void(void));
};
} // namespace FIRE

namespace
{
using ::testing::_;
using ::testing::Return;
constexpr auto title{"WindowTitle"};
constexpr auto width{200u};
constexpr auto height{400u};

class AWindow : public ::testing::Test
{
public:
    AWindow()
        : context(std::make_unique<FIRE::RenderContextMock>())
        , inputListener(std::make_unique<FIRE::InputListener>())
    {
    }
    FIRE::Window window{title, width, height};
    std::unique_ptr<FIRE::RenderContextMock> context;
    std::unique_ptr<FIRE::InputListener> inputListener;
};

} // namespace

TEST_F(AWindow, HasATitle)
{
    EXPECT_EQ(title, window.GetTitle());
}

TEST_F(AWindow, HasAWidth)
{
    EXPECT_EQ(width, window.GetWidth());
}

TEST_F(AWindow, HasAHeight)
{
    EXPECT_EQ(height, window.GetHeight());
}

TEST_F(AWindow, IsResizable)
{
    EXPECT_CALL(*context, Resize(150u, 300u));
    window.SetRenderContext(std::move(context));

    window.Resize(150u, 300u);
    EXPECT_EQ(150u, window.GetWidth());
    EXPECT_EQ(300u, window.GetHeight());
}

TEST_F(AWindow, CanBeClosed)
{
    EXPECT_CALL(*context, ShouldClose())
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    window.SetRenderContext(std::move(context));

    EXPECT_FALSE(window.ShouldClose());
    window.Close();
    EXPECT_TRUE(window.ShouldClose());
}

TEST_F(AWindow, ForwardsClosingToRenderContext)
{
    EXPECT_CALL(*context, Close());
    window.SetRenderContext(std::move(context));
    window.Close();
}

TEST_F(AWindow, ForwardsClosedCheckToRenderContext)
{
    EXPECT_CALL(*context, ShouldClose());
    window.SetRenderContext(std::move(context));
    window.ShouldClose();
}

TEST_F(AWindow, SupportsDoubleBuffering)
{
    EXPECT_CALL(*context, SwapBuffers());
    window.SetRenderContext(std::move(context));
    window.SwapBuffers();
}

TEST_F(AWindow, CanBePolledForEvents)
{
    EXPECT_CALL(*context, PollEvents());
    window.SetRenderContext(std::move(context));
    window.PollEvents();
}

TEST_F(AWindow, MayHaveAnInputListener)
{
    EXPECT_CALL(*context, RegisterInputListener(_));
    window.SetRenderContext(std::move(context));
    window.SetInputListener(std::move(inputListener));
}

TEST_F(AWindow, CanCaptureTheCursor)
{
    EXPECT_CALL(*context, CaptureCursor());
    window.SetRenderContext(std::move(context));
    window.CaptureCursor();
}

TEST_F(AWindow, CanReleaseTheCursor)
{
    EXPECT_CALL(*context, ReleaseCursor());
    window.SetRenderContext(std::move(context));
    window.ReleaseCursor();
}
