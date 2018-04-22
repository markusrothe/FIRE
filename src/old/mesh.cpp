#include "mesh.h"
#include <iostream>
#include <utility>

namespace blocks
{
    Mesh::Mesh()
        : m_vertices()
        , m_normals()
        , m_texCoords()
        , m_indices()
    {

    }

    Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals
        , std::vector<glm::vec2> texCoords, std::vector<unsigned int> indices)
        : m_vertices(vertices)
        , m_normals(normals)
        , m_texCoords(texCoords)
        , m_indices(indices)
    {
    }

    std::vector<glm::vec3> const& Mesh::GetVertices() const
    {
        return m_vertices;
    }

    std::vector<glm::vec3> const& Mesh::GetNormals() const
    {
        return m_normals;
    }

    std::vector<glm::vec2> const& Mesh::GetTexCoords() const
    {
        return m_texCoords;
    }

    std::vector<unsigned int> const& Mesh::GetIndices() const
    {
        return m_indices;
    }

    Mesh CreateCube()
    {
        std::vector<glm::vec3> const vertices = {
            glm::vec3(-1, -1,  1), // left bottom front
            glm::vec3(-1, -1, -1), // left bottom back
            glm::vec3(1, -1,  1), // right bottom front
            glm::vec3(1, -1, -1), // right bottom back
            glm::vec3(-1,  1,  1), // left top front
            glm::vec3(-1,  1, -1), // left top back
            glm::vec3(1,  1,  1), // right top front
            glm::vec3(1,  1, -1)  // right top back 
        };

        std::vector<glm::vec3> normals = vertices;
        for (auto& normal : normals)
        {
            normal = glm::normalize(normal);
        }

        std::vector<glm::vec2> colors;
        std::vector<unsigned int> const indices = {
            0, 1, 2, 2, 1, 3,
            0, 2, 4, 4, 2, 6,
            2, 3, 6, 6, 3, 7,
            3, 1, 7, 7, 1, 5,
            1, 0, 5, 5, 0, 4,
            4, 6, 5, 5, 6, 7
        };

        return Mesh(std::move(vertices), std::move(normals), std::move(colors), std::move(indices));
    }

    

}
