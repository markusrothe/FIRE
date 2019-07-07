#include <FIRE/Mesh3D.h>
#include <algorithm>
#include <cassert>
namespace FIRE
{

Mesh3D::Mesh3D(std::string name)
    : m_name{std::move(name)}
    , m_positions{}
    , m_indices{}
{
}

std::string Mesh3D::Name() const
{
    return m_name;
}

void Mesh3D::AddPosition(glm::vec3 vertex)
{
    m_positions.push_back(std::move(vertex));
}

void Mesh3D::AddPositions(std::vector<glm::vec3> vertices)
{
    m_positions.insert(m_positions.end(), vertices.begin(), vertices.end());
}

std::vector<glm::vec3> Mesh3D::Positions() const
{
    return m_positions;
}

void Mesh3D::AddIndex(unsigned int idx)
{
    assert(idx < m_positions.size());
    m_indices.push_back(idx);
}

void Mesh3D::AddIndices(std::vector<unsigned int> indices)
{
    auto const vertexCount = m_positions.size();

    assert(
        std::find_if(indices.begin(), indices.end(), [vertexCount](auto index) {
            return index >= vertexCount;
        }) == indices.end());

    m_indices.insert(m_indices.end(), indices.begin(), indices.end());
}

std::vector<unsigned int> Mesh3D::Indices() const
{
    return m_indices;
}

void Mesh3D::AddNormal(glm::vec3 normal)
{
    m_normals.push_back(std::move(normal));
}

void Mesh3D::AddNormals(std::vector<glm::vec3> normals)
{
    m_normals.insert(m_normals.end(), normals.begin(), normals.end());
}

std::vector<glm::vec3> Mesh3D::Normals() const
{
    return m_normals;
}

VertexDeclaration& Mesh3D::GetVertexDeclaration()
{
    return m_vertexDeclaration;
}

VertexDeclaration const& Mesh3D::GetVertexDeclaration() const
{
    return m_vertexDeclaration;
}
} // namespace FIRE
