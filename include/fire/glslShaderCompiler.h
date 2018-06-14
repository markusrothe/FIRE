#ifndef fire_glslshadercompiler_h
#define fire_glslshadercompiler_h

#include "shaderCompiler.h"

namespace Fire
{
    class GLSLShaderCompiler : public ShaderCompiler
    {
    public:
        GLSLShaderCompiler(std::string const& code, ShaderType shaderType);
        
        int Compile() override;
        
    private:
        std::string m_code;
        ShaderType m_shaderType;
    };
} // namespace Fire

#endif // fire_glslshadercompiler_h
