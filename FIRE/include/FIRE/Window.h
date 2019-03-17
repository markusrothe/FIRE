#ifndef FIRE_Window_h
#define FIRE_Window_h

#include <memory>
#include <string>

namespace FIRE
{
class RenderContext;
class Window
{
public:
    explicit Window(
        std::string const title, unsigned int width, unsigned int height);

    ~Window();

    std::string GetTitle() const;

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    void Resize(unsigned int newWidth, unsigned int newHeight);
    bool ShouldClose() const;
    void Close();

    void SetRenderContext(std::unique_ptr<RenderContext> context);
    void PollEvents();
    void SwapBuffers();

private:
    std::string const m_title;
    unsigned int m_width;
    unsigned int m_height;
    std::unique_ptr<RenderContext> m_context;
};
} // namespace FIRE

#endif // FIRE_Window_h
