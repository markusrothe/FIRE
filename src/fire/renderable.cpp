#include "renderable.h"

namespace Fire
{
    Renderable::Renderable(std::string const& name)
        : m_name(name)
    {
    }

    std::string Renderable::GetName() const
    {
        return m_name;
    }

    void Renderable::SetVertexDeclaration(VertexDeclaration const& vDecl)
    {
        m_vDecl = vDecl;
    }
    
    VertexDeclaration const& Renderable::GetVertexDeclaration() const
    {
        return m_vDecl;
    }
    
} // namespace Fire
