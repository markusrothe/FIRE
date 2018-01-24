#ifndef blocks_entity_h
#define blocks_entity_h

#include "assets.h"
#include "transform.h"
#include <string>
#include <glm/glm.hpp>

namespace blocks
{
    class Entity
    {
    public:
        explicit Entity(std::string const name);

        std::string GetName() const;
        Assets& GetAssets();
        Transform& GetTransform();
        glm::mat4x4 const& GetModelMatrix() const;        

    private:
        std::string const m_name;
        Assets m_assets;
        Transform m_transform;
    };
}

#endif // blocks_entity_h
