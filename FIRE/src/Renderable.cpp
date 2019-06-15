#include <FIRE/Renderable.h>
#include <FIRE/Transform.h>
#include <utility>
namespace FIRE
{

class Renderable::Impl
{
public:
    Impl(std::string name)
        : m_name(std::move(name))
    {
    }

    std::string m_name;
    Mesh m_mesh{""};
    std::pair<std::string, Matrix4x4> m_uniformVals;
    Transform m_transform;
    Material m_material;
};

Renderable::Renderable(std::string name)
    : m_impl(std::make_unique<Renderable::Impl>(std::move(name)))
{
}

Renderable::~Renderable() = default;

void Renderable::SetMesh(Mesh mesh)
{
    m_impl->m_mesh = std::move(mesh);
}

Mesh& Renderable::GetMesh()
{
    return m_impl->m_mesh;
}

Mesh const& Renderable::GetMesh() const
{
    return m_impl->m_mesh;
}

void Renderable::SetName(std::string name)
{
    m_impl->m_name = std::move(name);
}

std::string Renderable::Name() const
{
    return m_impl->m_name;
}

void Renderable::SetMaterial(Material material)
{
    m_impl->m_material = std::move(material);
}

Material const& Renderable::GetMaterial() const
{
    return m_impl->m_material;
}

Material& Renderable::GetMaterial()
{
    return m_impl->m_material;
}

Transform& Renderable::GetTransform()
{
    return m_impl->m_transform;
}

bool operator==(Renderable const& lhs, Renderable const& rhs)
{
    return lhs.Name() == rhs.Name();
}

bool operator!=(Renderable const& lhs, Renderable const& rhs)
{
    return !(lhs == rhs);
}

} // namespace FIRE
