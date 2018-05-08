
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

    std::vector<glm::vec3> const& VertexData::GetPositions() const
    {
        return m_positions;
    }

    std::vector<glm::vec3> const& VertexData::GetNormals() const
    {
        return m_normals;
    }

    std::vector<glm::vec3> const& VertexData::GetTexCoords() const
    {
        return m_texCoords;
    }

    std::vector<glm::vec3> const& VertexData::GetColors() const
    {
        return m_colors;
    }

    void VertexData::AddPosition(glm::vec3 const& pos)
    {        
        AddToContainer(m_positions, pos);
    }

    void VertexData::AddNormal(glm::vec3 const& normal)
    {
        AddToContainer(m_normals, normal);
    }

    void VertexData::AddTexCoord(glm::vec3 const& texCoord)
    {
        AddToContainer(m_texCoords, texCoord);
    }

    void VertexData::AddColor(glm::vec3 const& color)
    {
        AddToContainer(m_colors, color);
    }

    bool VertexData::IsDirty() const
    {
        return m_isDirty;
    }

    void VertexData::ClearDirtyFlag()
    {
        SetDirtyFlag(false);
    }
    
    void VertexData::SetDirtyFlag(bool dirty)
    {
        m_isDirty = dirty;
    }

    void VertexData::AddToContainer(std::vector<glm::vec3>& container, glm::vec3 const& value)
    {
        container.push_back(value);
        SetDirtyFlag(true);
    }
} // namespace Fire

