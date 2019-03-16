#include <FIRE/GLRenderContext.h>
#include <FIRE/Window.h>
#include <chrono>
#include <iostream>
#include <thread>

int main(int, char**)
{
    FIRE::Window window{"example1", 300, 300};

    FIRE::GLRenderContext context(window);

    auto windowCloser = std::thread([&window] {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Closing window now\n";
        window.Close();
    });

    while(!window.ShouldClose())
    {
        window.SwapBuffers();
    }

    windowCloser.join();
}
