#ifndef fire_scene_h
#define fire_scene_h

#include <string>

namespace Fire
{
    class Scene
    {
    public:
        explicit Scene(std::string const& sceneName);

        std::string GetName() const;
    private:
        std::string const m_name;
    };
    
} // namespace Fire

#endif // fire_scene_h
