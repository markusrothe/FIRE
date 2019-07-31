#ifndef FIRE_Mesh_h
#define FIRE_Mesh_h

#include <FIRE/MeshType.h>
#include <FIRE/VertexDeclaration.h>
#include <FIRE/glmfwd.h>
#include <string>
#include <vector>
namespace FIRE
{

class Mesh3D
{
public:
    explicit Mesh3D(std::string name, MeshType meshType);

    std::string Name() const;
    void AddPosition(glm::vec3 vertex);
    void AddPositions(std::vector<glm::vec3> positions);
    std::vector<glm::vec3> Positions() const;

    void AddIndex(unsigned int idx);
    void AddIndices(std::vector<unsigned int> indices);
    std::vector<unsigned int> Indices() const;

    void AddNormal(glm::vec3 normal);
    void AddNormals(std::vector<glm::vec3> normals);
    std::vector<glm::vec3> Normals() const;

    void AddUV(glm::vec2 uv);
    void AddUVs(std::vector<glm::vec2> uvs);
    std::vector<glm::vec2> UVs() const;

    VertexDeclaration& GetVertexDeclaration();
    VertexDeclaration const& GetVertexDeclaration() const;

    [[nodiscard]] MeshType GetMeshType() const;

private:
    std::string m_name;

    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec2> m_uvs;
    std::vector<unsigned int> m_indices;

    VertexDeclaration m_vertexDeclaration;
    MeshType m_meshType;
};

} // namespace FIRE

#endif
