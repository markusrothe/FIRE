#ifndef blocks_mesh_h
#define blocks_mesh_h

#include <glm/glm.hpp>
#include <vector>

namespace blocks
{
    class Mesh
    {
    public:
        Mesh();

        Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals
            , std::vector<glm::vec2> texCoords, std::vector<unsigned int> indices);

        std::vector<glm::vec3> const& GetVertices() const;
        std::vector<glm::vec3> const& GetNormals() const;
        std::vector<glm::vec2> const& GetTexCoords() const;
        std::vector<unsigned int> const& GetIndices() const;

    private:
        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec2> m_texCoords;
        std::vector<unsigned int> m_indices;
    };

    Mesh CreateCube();
}

#endif //blocks_mesh_h
