#ifndef fire_material_f
#define fire_material_f

#include "shader.h"
#include <memory>
#include <string>
#include <vector>

namespace Fire
{
class Material
{
public:
    Material(std::string const& name, std::unique_ptr<Shader>&& shader);

    ~Material();

    std::string GetName() const;

    void Bind();
    void Unbind();

    bool IsBound() const;

private:
    std::string const m_name;
    std::unique_ptr<Shader> m_shader;
    bool m_bound;
};
} // namespace Fire

#endif // fire_material_h
