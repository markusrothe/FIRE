#ifndef FIRE_GLShaderFactory_h
#define FIRE_GLShaderFactory_h

#include <ShaderFactory.h>
#include <string>
namespace FIRE
{
class GLShaderFactory : public ShaderFactory
{
public:
    unsigned int CreateDefaultShader() override;
    unsigned int Create(std::vector<std::pair<ShaderType, std::string>> const& shaderCode) override;
};

} // namespace FIRE

#endif // !FIRE_GLShaderFactory_h
