#ifndef fire_renderable_h
#define fire_renderable_h

#include "vertexDeclaration.h"
#include <string>

namespace Fire
{
    struct VertexData;
    
    class Renderable
    {
    public:
        explicit Renderable(std::string const& name);
        std::string GetName() const;

        void SetVertexDeclaration(VertexDeclaration const& vDecl);
        VertexDeclaration const& GetVertexDeclaration() const;
        
    private:
        std::string const m_name;
        VertexDeclaration m_vDecl;
    };
} // namespace Fire

#endif // fire_renderable_h
