#ifndef blocks_materialConfigParser_h
#define blocks_materialConfigParser_h

#include "materialConfig.h"
#include <string>
#include <vector>

namespace blocks
{   
    class MaterialConfigParser
    {
    public:
        explicit MaterialConfigParser(std::string const materialConfigFile);	

        std::vector<MaterialConfig> GetMaterialConfigs() const;
        
    private:

        std::string ParseName();

        std::string ParseBasePath();

        std::string ParseShaderPath(std::string const shaderType);

        std::vector<std::string> ParseLocations();

        std::vector<MaterialConfig> m_materialConfigs;

        std::vector<std::string> m_currentLineTokens;
    };
}

#endif // blocks_materialConfigParser_h
