#ifndef FIRE_Mesh_h
#define FIRE_Mesh_h

#include <FIRE/Vector.h>
#include <FIRE/VertexDeclaration.h>
#include <string>
#include <vector>
namespace FIRE
{
struct Mesh
{
    explicit Mesh(std::string name);

    std::string Name() const;
    void AddVertex(Vector3 vertex);
    void AddVertices(std::initializer_list<Vector3> vertices);
    std::vector<Vector3> Vertices() const;
    std::vector<float> VerticesAsArray() const;

    void AddIndex(unsigned int idx);
    void AddIndices(std::initializer_list<unsigned int> indices);
    std::vector<unsigned int> Indices() const;

    void AddNormal(Vector3 normal);
    void AddNormals(std::initializer_list<Vector3> normals);
    std::vector<Vector3> Normals() const;
    std::vector<float> NormalsAsArray() const;

    VertexDeclaration& GetVertexDeclaration();
    VertexDeclaration const& GetVertexDeclaration() const;

private:
    std::string m_name;

    std::vector<Vector3> m_vertices;
    std::vector<Vector3> m_normals;
    std::vector<unsigned int> m_indices;

    VertexDeclaration m_vertexDeclaration;
};
} // namespace FIRE

#endif
