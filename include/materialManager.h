#ifndef materialManager_h
#define materialManager_h

#include "material.h"
#include "materialMap.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <memory>

namespace blocks
{
    class MaterialManager
    {
    public:
        explicit MaterialManager(std::string const materialConfigurationFile);

        Material const* GetMaterial(std::string const name) const;

    private:
        MaterialMap m_materialMap;
    };
}

#endif // materialManager_h
