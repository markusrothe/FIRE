#ifndef fire_shader_h
#define fire_shader_h

#include <string>
#include <memory>

namespace Fire
{
    class ShaderCompiler;
    
    class Shader
    {
    public:
        Shader(std::string const& name,
               std::unique_ptr<ShaderCompiler> const& compiler);

        std::string const& GetName() const;

        void Bind();

        bool Bound() const;
    private:
        std::string const m_name;
        bool m_bound;
    };
    
} // namespace Fire

#endif // fire_shader_h
