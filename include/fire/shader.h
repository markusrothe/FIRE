#ifndef fire_shader_h
#define fire_shader_h

#include <memory>
#include <string>

namespace Fire
{
class ShaderCompiler;

class Shader
{
public:
    virtual ~Shader() = default;

    virtual std::string const& GetName() const = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual bool Bound() const = 0;
};

} // namespace Fire

#endif // fire_shader_h
