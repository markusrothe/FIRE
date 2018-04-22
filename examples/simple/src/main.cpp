#include <fire/root.h>
#include <fire/sceneManager.h>
#include <fire/scene.h>
#include <fire/renderer.h>

int main(int, char**)
{
    auto const windowWidth = 1200u;
    auto const windowHeight = 800u;
    Fire::Root root("WindowName", windowWidth, windowHeight);

    Fire::SceneManager sceneManager(root);
    Fire::Scene& mainScene = sceneManager.CreateScene("mainScene");
    Fire::Renderer renderer(root, sceneManager);

    while (true)
    {
        sceneManager.Update();
        renderer.Render();
    }
}
