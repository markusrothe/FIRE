
#include "vertexData.h"

namespace Fire
{
    VertexData::VertexData()
        : m_positions()
        , m_normals()
        , m_texCoords()
        , m_colors()
        , m_isDirty(false)
    {
       
    }

    std::vector<glm::vec3> VertexData::GetPositions() const
    {
        return m_positions;
    }

    std::vector<glm::vec3> VertexData::GetNormals() const
    {
        return m_normals;
    }

    std::vector<glm::vec3> VertexData::GetTexCoords() const
    {
        return m_texCoords;
    }

    std::vector<glm::vec3> VertexData::GetColors() const
    {
        return m_colors;
    }

    bool VertexData::IsDirty() const
    {
        return m_isDirty;
    }

    void VertexData::AddPosition(glm::vec3 const& pos)
    {        
        m_positions.push_back(pos);
        m_isDirty = true;
    }

    void VertexData::AddNormal(glm::vec3 const& normal)
    {
        m_normals.push_back(normal);
        m_isDirty = true;
    }

    void VertexData::AddTexCoord(glm::vec3 const& texCoord)
    {
        m_texCoords.push_back(texCoord);
        m_isDirty = true;
    }

    void VertexData::AddColor(glm::vec3 const& color)
    {
        m_colors.push_back(color);
        m_isDirty = true;
    }
    
} // namespace Fire

