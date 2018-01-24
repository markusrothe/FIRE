#ifndef blocks_materialConfig_h
#define blocks_materialConfig_h

#include <string>
#include <vector>

namespace blocks
{
    struct MaterialConfig
    {
        std::string m_name;
        std::string m_vertexShaderPath;
        std::string m_fragmentShaderPath;
        std::vector<std::string> m_locations;
    };
}

#endif // blocks_materialConfig_h
