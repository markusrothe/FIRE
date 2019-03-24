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

std::string Renderable::GetName() const
{
    return m_name;
}

std::string Renderable::GetMaterial() const
{
    return m_material;
}

bool operator==(Renderable const& lhs, Renderable const& rhs)
{
    return lhs.GetName() == rhs.GetName();
}

bool operator!=(Renderable const& lhs, Renderable const& rhs)
{
    return !(lhs == rhs);
}

} // namespace FIRE
