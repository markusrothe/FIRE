#ifndef fire_renderer_h
#define fire_renderer_h

namespace Fire
{
    class Root;
    class SceneManager;

    class Renderer
    {
    public:
        Renderer(Root const& root, SceneManager const& sceneManager);

        void Render();

    private:
        Root const& m_root;
        SceneManager const& m_sceneManager;
    };

} // namespace Fire

#endif // fire_renderer_h
