#include <FIRE/Mesh.h>
#include <algorithm>
#include <cassert>
namespace FIRE
{

namespace
{
std::vector<float> FlattenVectors(std::vector<Vector3> const& vecs)
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
    : m_name{name}
    , m_vertices{}
    , m_indices{}
{
}

std::string Mesh::Name() const
{
    return m_name;
}

void Mesh::AddVertex(Vector3 vertex)
{
    m_vertices.push_back(std::move(vertex));
}

void Mesh::AddVertices(std::initializer_list<Vector3> vertices)
{
    m_vertices.insert(m_vertices.end(), vertices);
}

std::vector<Vector3> Mesh::Vertices() const
{
    return m_vertices;
}

std::vector<float> Mesh::VerticesAsArray() const
{
    return FlattenVectors(m_vertices);
}

void Mesh::AddIndex(unsigned int idx)
{
    assert(idx < m_vertices.size());
    m_indices.push_back(idx);
}

void Mesh::AddIndices(std::initializer_list<unsigned int> indices)
{
    auto const vertexCount = m_vertices.size();

    assert(
        std::find_if(indices.begin(), indices.end(), [vertexCount](auto index) {
            return index >= vertexCount;
        }) == indices.end());

    m_indices.insert(m_indices.end(), indices);
}

std::vector<unsigned int> Mesh::Indices() const
{
    return m_indices;
}

void Mesh::AddNormal(Vector3 normal)
{
    m_normals.push_back(std::move(normal));
}

void Mesh::AddNormals(std::initializer_list<Vector3> normals)
{
    m_normals.insert(m_normals.end(), normals);
}

std::vector<Vector3> Mesh::Normals() const
{
    return m_normals;
}

std::vector<float> Mesh::NormalsAsArray() const
{
    return FlattenVectors(m_normals);
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
