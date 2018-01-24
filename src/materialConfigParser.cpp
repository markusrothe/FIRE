#include "materialConfigParser.h"
#include "tokenize.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <utility>

namespace blocks
{
    namespace
    {
        std::string const namePrefix("name=");
        std::string const pathPrefix("path=");
        std::string const shadersPrefix("shaders=");
        std::string const locationsPrefix("locations=");

        unsigned int FindTokenIndex(std::vector<std::string> const& tokens, std::string const tokenPrefix)
        {
            auto idx = 0;
            for (auto const token : tokens)
            {
                if (tokenPrefix.size() <= token.size())
                {
                    auto result = std::mismatch(std::begin(tokenPrefix), std::end(tokenPrefix), std::begin(token));
                    if (result.first == std::end(tokenPrefix))
                    {
                        return idx;
                    }
                }

                ++idx;
            }

            return std::numeric_limits<unsigned int>::max();
        }
    } // namespace

    MaterialConfigParser::MaterialConfigParser(std::string const materialConfigFile)
        : m_materialConfigs()
        , m_currentLineTokens()
    {
        std::ifstream ifs(materialConfigFile);

        std::string line;
        while (std::getline(ifs, line))
        {
            m_currentLineTokens.clear();
            std::cout << "parsing material: " << line << std::endl;
            MaterialConfig config;
            Tokenize(line, m_currentLineTokens, " ");
            
            config.m_name = ParseName();
            config.m_vertexShaderPath = ParseShaderPath("vs");
            config.m_fragmentShaderPath = ParseShaderPath("fs");
            config.m_locations = ParseLocations();

            m_materialConfigs.push_back(config);
        }
    }

    std::vector<MaterialConfig> MaterialConfigParser::GetMaterialConfigs() const
    {
        return m_materialConfigs;
    }

    std::string MaterialConfigParser::ParseName()
    {
        auto const tokenIndex = FindTokenIndex(m_currentLineTokens, namePrefix);
        auto nameToken = m_currentLineTokens[tokenIndex];
        nameToken.erase(0, namePrefix.size());

        return nameToken;
    }

    std::string MaterialConfigParser::ParseBasePath()
    {
        auto const tokenIndex = FindTokenIndex(m_currentLineTokens, pathPrefix);
        auto pathToken = m_currentLineTokens[tokenIndex];
        pathToken.erase(0, pathPrefix.size());

        return pathToken;
    }

    std::string MaterialConfigParser::ParseShaderPath(std::string const shaderType)
    {
        auto const tokenIndex = FindTokenIndex(m_currentLineTokens, shadersPrefix);
        auto const shadersToken = m_currentLineTokens[tokenIndex];

        if (shadersToken.find(shaderType) != std::string::npos)
        {
            return ParseBasePath() + "." + shaderType;
        }

        return "";
    }

    std::vector<std::string> MaterialConfigParser::ParseLocations()
    {
        auto const tokenIndex = FindTokenIndex(m_currentLineTokens, locationsPrefix);
        auto locationsToken = m_currentLineTokens[tokenIndex];
        locationsToken.erase(0, locationsPrefix.size());
        
        std::vector<std::string> locations;
        Tokenize(locationsToken, locations, ",");
        
        return locations;
    }

} // namespace blocks
