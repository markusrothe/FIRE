#include "fire/windowFactory.h"
#include "fire/window.h"
#include "fire/scene.h"
#include <memory>

int main(int, char**)
{
    auto const windowWidth = 1200u;
    auto const windowHeight = 800u;

    auto window = Fire::WindowFactory::CreateGLWindow("name", windowWidth, windowHeight);

    Fire::Scene mainScene("sceneName");




    /*
    Fire::SceneManager sceneManager;

    
    sceneManager.AddScene(mainScene);

    Fire::Renderer renderer(window, sceneManager);
    */

    while (!window->ShouldClose())
    {
        window->PollEvents();
        mainScene.Update();
        /*sceneManager.Update();
          renderer.Render();*/

        window->SwapBuffers();
    }
}
