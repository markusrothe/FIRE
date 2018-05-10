#include "fire/window.h"
#include "fire/renderContext.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

namespace
{
    std::string const& windowName = "windowName";
    auto const windowWidth = 200;
    auto const windowHeight = 300;

    class RenderContextMock : public Fire::RenderContext
    {
    public:
        virtual ~RenderContextMock(){}

        MOCK_METHOD0(ShouldClose, bool());
        MOCK_METHOD0(PollEvents, void());
        MOCK_METHOD0(SwapBuffers, void());
    };

    class WindowTest : public ::testing::Test
    {
    public:
        WindowTest()
            : m_renderContextMock(std::make_unique<RenderContextMock>())
            , m_renderContext(m_renderContextMock.get())
            , m_window(std::make_unique<Fire::Window>(windowName, windowWidth
                                                      , windowHeight, std::move(m_renderContextMock)))
        {

        }

    private:
        std::unique_ptr<RenderContextMock> m_renderContextMock;

    protected:
        RenderContextMock* m_renderContext;
        std::unique_ptr<Fire::Window> m_window;
    };

} // namespace

TEST_F(WindowTest, WindowsHaveAName)
{
    EXPECT_EQ(m_window->GetName(), windowName);
}

TEST_F(WindowTest, WindowsHaveAWidth)
{
    EXPECT_EQ(m_window->GetWidth(), windowWidth);
}

TEST_F(WindowTest, WindowsHaveAHeight)
{
    EXPECT_EQ(m_window->GetHeight(), windowHeight);
}

TEST_F(WindowTest, WindowsInitialzeARenderContext)
{
    EXPECT_TRUE(m_window->GetRenderContext() != nullptr);
}

TEST_F(WindowTest, WindowsSupportBufferSwappingOfTheRenderContext)
{
    EXPECT_CALL(*m_renderContext, SwapBuffers())
        .Times(1);
    
    m_window->SwapBuffers();
}

TEST_F(WindowTest, WindowsCanBePolledForEventsOnTheRenderContext)
{
    EXPECT_CALL(*m_renderContext, PollEvents())
        .Times(1);
    
    m_window->PollEvents();
}

TEST_F(WindowTest, WindowsShouldCloseIfTheRenderContextCloses)
{
    EXPECT_CALL(*m_renderContext, ShouldClose())
        .Times(1)
        .WillOnce(::testing::Return(true));
    
    EXPECT_TRUE(m_window->ShouldClose());
}

TEST_F(WindowTest, WindowsShouldNotCloseIfTheRenderContextDoesNotClose)
{
    EXPECT_CALL(*m_renderContext, ShouldClose())
        .Times(1)
        .WillOnce(::testing::Return(false));
    
    EXPECT_FALSE(m_window->ShouldClose());
}
