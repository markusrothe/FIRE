#ifndef fire_renderable_h
#define fire_renderable_h

#include "vertexDeclaration.h"
#include "vertexData.h"
#include "uniformFunction.h"
#include <string>

namespace Fire
{
    class Material;
    class Renderable
    {
    public:
        explicit Renderable(std::string const& name);
        std::string GetName() const;

        void SetVertexDeclaration(VertexDeclaration const& vDecl);
        VertexDeclaration const& GetVertexDeclaration() const;
        
        VertexData& GetVertexData();
        Material* GetMaterial() const;

        void SetUniformFunction(UniformFunction func);
        UniformFunction GetUniformFunction() const;
        
    private:
        std::string const m_name;
        VertexDeclaration m_vDecl;
        VertexData m_vData;
        UniformFunction m_uniformFunction;
    };
} // namespace Fire

#endif // fire_renderable_h
