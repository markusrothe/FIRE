#include <FIRE/Mesh.h>
#include <algorithm>
#include <cassert>
namespace FIRE
{
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

void Mesh::AddVertex(Vertex vertex)
{
    m_vertices.push_back(std::move(vertex));
}

void Mesh::AddVertices(std::initializer_list<Vertex> vertices)
{
    m_vertices.insert(m_vertices.end(), vertices);
}

std::vector<Vertex> Mesh::Vertices() const
{
    return m_vertices;
}

std::vector<float> Mesh::VerticesAsArray() const
{
    std::vector<float> res;

    for(auto const& vertex : m_vertices)
    {
        res.push_back(vertex.x);
        res.push_back(vertex.y);
        res.push_back(vertex.z);
    }

    return res;
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

VertexDeclaration& Mesh::GetVertexDeclaration()
{
    return m_vertexDeclaration;
}

VertexDeclaration const& Mesh::GetVertexDeclaration() const
{
    return m_vertexDeclaration;
}
} // namespace FIRE
