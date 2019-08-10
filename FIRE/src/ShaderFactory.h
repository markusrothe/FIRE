#ifndef FIRE_ShaderFactory_h
#define FIRE_ShaderFactory_h

#include <FIRE/ShaderType.h>
#include <string>
#include <vector>

namespace FIRE
{
class ShaderFactory
{
public:
    virtual ~ShaderFactory() = default;
    virtual unsigned int CreateDefaultShader() = 0;
    virtual unsigned int Create(std::vector<std::pair<ShaderType, std::string>> const& shaderCode) = 0;
};
} // namespace FIRE

#endif // !FIRE_ShaderFactory_h
