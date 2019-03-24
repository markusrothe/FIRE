#ifndef FIRE_ShaderFactory_h
#define FIRE_ShaderFactory_h

namespace FIRE
{
class ShaderFactory
{
public:
    virtual ~ShaderFactory() = default;
    virtual unsigned int CreateDefaultShader() = 0;
};
} // namespace FIRE

#endif // !FIRE_ShaderFactory_h
