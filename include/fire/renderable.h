#ifndef fire_renderable_h
#define fire_renderable_h

#include "vertexDeclaration.h"
#include <string>

namespace Fire
{
    class VertexData;
    
    class Renderable
    {
    public:
        Renderable(std::string const& name
                   , VertexData const& vertexData
                   , VertexDeclaration const& vertexDeclaration);

        std::string GetName() const;

        VertexDeclaration const& GetVertexDeclaration() const;
        
    private:
        std::string const m_name;
        VertexDeclaration const m_vDecl;
    };
} // namespace Fire

#endif // fire_renderable_h
