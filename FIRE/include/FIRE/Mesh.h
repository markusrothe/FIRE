#ifndef FIRE_Mesh_h
#define FIRE_Mesh_h

#include <FIRE/Vertex.h>
#include <FIRE/VertexDeclaration.h>
#include <string>
#include <vector>
namespace FIRE
{
struct Mesh
{
    explicit Mesh(std::string name);

    std::string Name() const;
    void AddVertex(Vertex vertex);
    void AddVertices(std::initializer_list<Vertex> vertices);
    std::vector<Vertex> Vertices() const;
    std::vector<float> VerticesAsArray() const;

    void AddIndex(unsigned int idx);
    void AddIndices(std::initializer_list<unsigned int> indices);
    std::vector<unsigned int> Indices() const;

    VertexDeclaration& GetVertexDeclaration();
    VertexDeclaration const& GetVertexDeclaration() const;

private:
    std::string m_name;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    VertexDeclaration m_vertexDeclaration;
};
} // namespace FIRE

#endif
