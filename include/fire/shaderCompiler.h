#ifndef fire_shadercompiler_h
#define fire_shadercompiler_h

#include <string>

namespace Fire
{
    class ShaderCompiler
    {
    public:
        enum class ShaderType
        {
            VERTEX_SHADER,
            FRAGMENT_SHADER
        };
        
        virtual ~ShaderCompiler() = default;
        virtual int Compile() = 0;
        virtual int Link() = 0;
    };
} // namespace Fire

#endif // fire_shadercompiler_h
