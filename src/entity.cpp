#include "entity.h"


namespace blocks
{
    Entity::Entity(std::string const name)
        : m_name(name)
        , m_assets()
    {

    }

    std::string Entity::GetName() const
    {
        return m_name;
    }

    Assets& Entity::GetAssets()
    {
        return m_assets;
    }    

    Transform& Entity::GetTransform()
    {
        return m_transform;
    }
}
