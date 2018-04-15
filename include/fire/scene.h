#ifndef fire_scene_h
#define fire_scene_h

namespace Fire
{
    class Scene
    {
    public:
        explicit Scene(std::string_view const& sceneName);

    private:
        std::string_view const m_name;
    };
    
} // namespace Fire

#endif // fire_scene_h
