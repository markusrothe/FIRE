#include <FIRE/Mesh.h>
#include <algorithm>
#include <cassert>
namespace FIRE
{

namespace
{
std::vector<float> FlattenVectors(std::vector<glm::vec3> const& vecs)
{
    std::vector<float> result;
    for(auto const& vec : vecs)
    {
        result.push_back(vec.x);
        result.push_back(vec.y);
        result.push_back(vec.z);
    }
    return result;
}
} // namespace

Mesh::Mesh(std::string name)
    : m_name{std::move(name)}
    , m_positions{}
    , m_indices{}
{
}

std::string Mesh::Name() const
{
    return m_name;
}

void Mesh::AddPosition(glm::vec3 vertex)
{
    m_positions.push_back(std::move(vertex));
}

void Mesh::AddPositions(std::vector<glm::vec3> vertices)
{
    m_positions.insert(m_positions.end(), vertices.begin(), vertices.end());
}

void Mesh::AddPositions(std::vector<glm::vec2> positions)
{
    m_positions2D.insert(m_positions2D.end(), positions.begin(), positions.end());
}

std::vector<glm::vec3> Mesh::Positions() const
{
    return m_positions;
}

void Mesh::AddIndex(unsigned int idx)
{
    assert(idx < m_positions.size());
    m_indices.push_back(idx);
}

void Mesh::AddIndices(std::vector<unsigned int> indices)
{
    auto const vertexCount = m_positions.size();

    assert(
        std::find_if(indices.begin(), indices.end(), [vertexCount](auto index) {
            return index >= vertexCount;
        }) == indices.end());

    m_indices.insert(m_indices.end(), indices.begin(), indices.end());
}

std::vector<unsigned int> Mesh::Indices() const
{
    return m_indices;
}

void Mesh::AddNormal(glm::vec3 normal)
{
    m_normals.push_back(std::move(normal));
}

void Mesh::AddNormals(std::vector<glm::vec3> normals)
{
    m_normals.insert(m_normals.end(), normals.begin(), normals.end());
}

std::vector<glm::vec3> Mesh::Normals() const
{
    return m_normals;
}

VertexDeclaration& Mesh::GetVertexDeclaration()
{
    return m_vertexDeclaration;
}

VertexDeclaration const& Mesh::GetVertexDeclaration() const
{
    return m_vertexDeclaration;
}
} // namespace FIRE
