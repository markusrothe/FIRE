#ifndef fire_window_h
#define fire_window_h

#include <string>
#include <memory>

namespace Fire
{
    class RenderContext;

    class Window
    {
    public:
       
        Window(std::string const& windowName, unsigned int windowWidth,
               unsigned int windowHeight, std::unique_ptr<RenderContext>&& renderContext);

        ~Window();
        
        std::string GetName() const;
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        RenderContext* GetRenderContext() const;
        
        void SwapBuffers();
        
    private:
        std::string const m_windowName;
        unsigned int m_windowWidth;
        unsigned int m_windowHeight;

        std::unique_ptr<RenderContext> m_renderContext;
    };
} // namespace Fire

#endif // fire_window_h
