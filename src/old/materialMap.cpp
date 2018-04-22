#include "materialMap.h"

namespace blocks
{
    MaterialMapEntry CreateMaterialMapEntry(std::string const name, Material const& material)
    {
	return std::make_pair(name, material);
    }
}
