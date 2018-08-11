#ifndef fire_material_f
#define fire_material_f

#include <GL/glew.h>
#include <memory>
#include <string>
#include <vector>

namespace Fire
{
class Material
{
public:
    explicit Material(std::string const& name, GLuint shaderProgram);

    ~Material();

    std::string GetName() const;

    void Bind();
    void Unbind();
    bool IsBound() const;

    GLuint GetShader() { return m_shaderProgram; }

private:
    std::string const m_name;
    GLuint const m_shaderProgram;
    bool m_bound;
};
} // namespace Fire

#endif // fire_material_h
