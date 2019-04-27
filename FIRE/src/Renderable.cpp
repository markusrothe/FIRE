#include <FIRE/Renderable.h>

#include <utility>
namespace FIRE
{
Renderable::Renderable(std::string name)
    : m_name(std::move(name))
{
}

void Renderable::SetMesh(Mesh mesh)
{
    m_mesh = std::move(mesh);
}

Mesh& Renderable::GetMesh()
{
    return m_mesh;
}

Mesh const& Renderable::GetMesh() const
{
    return m_mesh;
}

void Renderable::SetName(std::string name)
{
    m_name = std::move(name);
}

std::string Renderable::Name() const
{
    return m_name;
}

std::string Renderable::GetMaterial() const
{
    return m_material;
}

bool operator==(Renderable const& lhs, Renderable const& rhs)
{
    return lhs.Name() == rhs.Name();
}

bool operator!=(Renderable const& lhs, Renderable const& rhs)
{
    return !(lhs == rhs);
}

std::pair<std::string, Matrix4x4> Renderable::GetShaderUniformMat4x4() const
{
    return m_uniformVals;
}

void Renderable::SetShaderUniformMat4x4(std::string const& uniformName, Matrix4x4 const& mat)
{
    m_uniformVals = std::make_pair(uniformName, mat);
}

} // namespace FIRE
