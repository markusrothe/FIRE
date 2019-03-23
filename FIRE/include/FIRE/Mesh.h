#ifndef FIRE_Mesh_h
#define FIRE_Mesh_h

#include <FIRE/Vertex.h>
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

private:
    std::string m_name;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};
} // namespace FIRE

#endif
