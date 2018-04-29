#include "fire/windowFactory.h"
#include "fire/window.h"
#include <memory>

int main(int, char**)
{
    auto const windowWidth = 1200u;
    auto const windowHeight = 800u;
    
    auto window = Fire::WindowFactory::CreateGLWindow("name", windowWidth, windowHeight);
    
    /*
      Fire::SceneManager sceneManager;
    
    Fire::Scene mainScene("sceneName");
    sceneManager.AddScene(mainScene);
    
    Fire::Renderer renderer(window, sceneManager);
    */
    
    while (!window->ShouldClose())
    {
        window->PollEvents();
        /*sceneManager.Update();
          renderer.Render();*/

        window->SwapBuffers();
    }
}
