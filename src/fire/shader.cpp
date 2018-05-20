#include "shader.h"
#include "shaderCompiler.h"

namespace Fire
{
    Shader::Shader(std::string const& name,
                   std::unique_ptr<ShaderCompiler> const& compiler)
        : m_name(name)
        , m_bound(false)
    {
        if (compiler)
        {
            compiler->Compile();
            compiler->Link();
        }
    }

    std::string const& Shader::GetName() const
    {
        return m_name;
    }

    void Shader::Bind()
    {
        m_bound = true;
    }
    
    bool Shader::Bound() const
    {
        return m_bound;
    }
} // namespace Fire
