#include "renderable.h"

namespace Fire
{
    Renderable::Renderable(std::string const& name, VertexData const& vertexData, VertexDeclaration const& vertexDeclaration)
        : m_name(name)
        , m_vDecl(vertexDeclaration)
    {
        (void) vertexData;
    }

    std::string Renderable::GetName() const
    {
        return m_name;
    }

    VertexDeclaration const& Renderable::GetVertexDeclaration() const
    {
        return m_vDecl;
    }
    
} // namespace Fire
