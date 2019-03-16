#include <gtest/gtest.h>

#include <string>

namespace FIRE
{
class Window
{
public:
    explicit Window(std::string const title, unsigned int width);

    std::string GetTitle() const;

    unsigned int GetWidth() const;

private:
    std::string const m_title;
    unsigned int m_width;
};

Window::Window(std::string const title, unsigned int width)
    : m_title(title)
    , m_width(width)
{
}

std::string Window::GetTitle() const { return m_title; }
unsigned int Window::GetWidth() const { return m_width; }

} // namespace FIRE

TEST(AWindow, HasATitle)
{
    FIRE::Window window("WindowTitle", 200u);
    EXPECT_EQ("WindowTitle", window.GetTitle());
}

TEST(AWindow, HasAWidth)
{
    FIRE::Window window("WindowTitle", 200u);
    EXPECT_EQ(200u, window.GetWidth());
}