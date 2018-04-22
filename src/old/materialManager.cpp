#include "compileMaterial.h"
#include "materialManager.h"
#include "materialConfigParser.h"
#include <iostream>
#include <GL/glew.h>
#include <vector>

namespace blocks
{
    MaterialManager::MaterialManager(std::string const materialConfigurationFile)
        : m_materialMap()
    {
        std::cout << "Parsing file " << materialConfigurationFile << std::endl;

        MaterialConfigParser configParser(materialConfigurationFile);

        auto const& configs = configParser.GetMaterialConfigs();

        for (auto const& config : configs)
        {
            m_materialMap.insert(CompileMaterial(config));
        }
    }

    Material const* MaterialManager::GetMaterial(std::string const name) const
    {
        auto it = m_materialMap.find(name);

        if (it != std::end(m_materialMap))
        {
            return &(it->second);
        }
        else
        {
            return nullptr;
        }
    }
} // namespace blocks
