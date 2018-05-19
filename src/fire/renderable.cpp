#include "renderable.h"
#include "material.h"

namespace Fire
{
    namespace
    {
        Material dummy("");
    } // namespace
    
    Renderable::Renderable(std::string const& name)
        : m_name(name)
        , m_vDecl{}
        , m_vData{}
        , m_uniformFunction([](){})
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
    
    VertexData& Renderable::GetVertexData()
    {
        return m_vData;
    }

    Material* Renderable::GetMaterial() const
    {
        return &dummy;
    }

    void Renderable::SetUniformFunction(UniformFunction func)
    {
        m_uniformFunction = func;
    }
    
    UniformFunction Renderable::GetUniformFunction() const
    {
        return m_uniformFunction;
    }
} // namespace Fire
