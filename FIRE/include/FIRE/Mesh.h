#ifndef FIRE_Mesh_h
#define FIRE_Mesh_h

#include <FIRE/Vector.h>
#include <FIRE/VertexDeclaration.h>
#include <string>
#include <vector>
namespace FIRE
{
class Mesh
{
public:
    explicit Mesh(std::string name);

    std::string Name() const;
    void AddPosition(Vector3 vertex);
    void AddPositions(std::vector<Vector3> positions);
    std::vector<Vector3> Positions() const;
    std::vector<float> PositionsAsArray() const;

    void AddIndex(unsigned int idx);
    void AddIndices(std::vector<unsigned int> indices);
    std::vector<unsigned int> Indices() const;

    void AddNormal(Vector3 normal);
    void AddNormals(std::vector<Vector3> normals);
    std::vector<Vector3> Normals() const;
    std::vector<float> NormalsAsArray() const;

    VertexDeclaration& GetVertexDeclaration();
    VertexDeclaration const& GetVertexDeclaration() const;

private:
    std::string m_name;

    std::vector<Vector3> m_positions;
    std::vector<Vector3> m_normals;
    std::vector<unsigned int> m_indices;

    VertexDeclaration m_vertexDeclaration;
};
} // namespace FIRE

#endif
