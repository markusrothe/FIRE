#ifndef fire_vertexdata_h
#define fire_vertexdata_h

#include <glm/glm.hpp>
#include <vector>

namespace Fire
{
    struct VertexData
    {       
        VertexData();

        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec3> m_texCoords;
        std::vector<glm::vec3> m_colors;
    };
    
} // namespace Fire

#endif // fire_vertexdata_h
