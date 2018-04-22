#ifndef blocks_window_h
#define blocks_window_h

#include <GLFW/glfw3.h>
#include <string>

namespace blocks
{
    class KeyHandler;

    class Window
    {
    public:
        Window(unsigned int width, unsigned int height, std::string const name, KeyHandler& keyHandler);

        void KeyPressed(int key, int action);

        bool WindowShouldClose() const;

        void PollEvents() const;
        void SwapBuffers() const;

    private:
        GLFWwindow* m_window;
        KeyHandler& m_keyHandler;
    };
}

#endif