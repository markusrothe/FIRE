#ifndef FIRE_GLShaderFactory_h
#define FIRE_GLShaderFactory_h

#include "ShaderFactory.h"

namespace FIRE
{
class GLShaderFactory : public ShaderFactory
{
public:
    unsigned int CreateDefaultShader() override;
};

} // namespace FIRE

#endif // !FIRE_GLShaderFactory_h
