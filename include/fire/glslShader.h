#ifndef fire_glslshader_h
#define fire_glslshader_h

#include "shader.h"

namespace Fire
{
class GLSLShader : public Shader
{
public:
    explicit GLSLShader(std::string name);

    virtual std::string const& GetName() const override;

    virtual void Bind() override;
    virtual void Unbind() override;
    virtual bool Bound() const override;

private:
    std::string m_name;
    bool m_bound;
};

} // namespace Fire

#endif // fire_glslshader_h
