#ifndef FIRE_Mesh_h
#define FIRE_Mesh_h

#include <FIRE/VertexDeclaration.h>
#include <FIRE/glmfwd.h>
#include <string>
#include <vector>
namespace FIRE
{

enum class MeshType
{
    Plane,
    Cube,
    Sphere,
    Rect2D
};

class Mesh
{
public:
    explicit Mesh(std::string name);

    std::string Name() const;
    void AddPosition(glm::vec3 vertex);
    void AddPositions(std::vector<glm::vec3> positions);
    void AddPositions(std::vector<glm::vec2> positions);
    std::vector<glm::vec3> Positions() const;

    void AddIndex(unsigned int idx);
    void AddIndices(std::vector<unsigned int> indices);
    std::vector<unsigned int> Indices() const;

    void AddNormal(glm::vec3 normal);
    void AddNormals(std::vector<glm::vec3> normals);
    std::vector<glm::vec3> Normals() const;

    VertexDeclaration& GetVertexDeclaration();
    VertexDeclaration const& GetVertexDeclaration() const;

private:
    std::string m_name;

    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec2> m_positions2D;

    std::vector<glm::vec3> m_normals;
    std::vector<unsigned int> m_indices;

    VertexDeclaration m_vertexDeclaration;
};

struct MeshHandle
{
    std::string name;
    MeshType type;
};

} // namespace FIRE

#endif
