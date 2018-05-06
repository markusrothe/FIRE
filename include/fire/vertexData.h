#ifndef fire_vertexdata_h
#define fire_vertexdata_h

#include <glm/glm.hpp>
#include <vector>

namespace Fire
{
    class VertexData
    {
    public:
        VertexData();

        std::vector<glm::vec3> GetPositions() const;
        std::vector<glm::vec3> GetNormals() const;
        std::vector<glm::vec3> GetTexCoords() const;
        std::vector<glm::vec3> GetColors() const;

        bool IsDirty() const;

        void AddPosition(glm::vec3 const& pos);
        void AddNormal(glm::vec3 const& normal);
        void AddTexCoord(glm::vec3 const& texCoord);
        void AddColor(glm::vec3 const& color);
        
    private:        
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec3> m_texCoords;
        std::vector<glm::vec3> m_colors;
        bool m_isDirty;
    };
    
} // namespace Fire

#endif // fire_vertexdata_h
