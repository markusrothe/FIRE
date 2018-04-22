#ifndef blocks_entity_h
#define blocks_entity_h

#include "assets.h"
#include "transform.h"
#include "glmForward.h"
#include <string>

namespace blocks
{
    class Entity
    {
    public:
        explicit Entity(std::string const name);

        std::string GetName() const;
        Assets& GetAssets();
        Transform& GetTransform();

    private:
        std::string const m_name;
        Assets m_assets;
        Transform m_transform;
    };
}

#endif // blocks_entity_h
