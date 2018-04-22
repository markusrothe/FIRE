#ifndef blocks_materialMap_h
#define blocks_materialMap_h

#include "material.h"
#include <string>
#include <unordered_map>
#include <utility>

namespace blocks
{
    typedef std::pair<std::string, Material> MaterialMapEntry;
    typedef std::unordered_map<std::string, Material> MaterialMap;

    MaterialMapEntry CreateMaterialMapEntry(std::string const name, Material const& material);
}

#endif // blocks_materialMap_h
