#ifndef fire_renderable_h
#define fire_renderable_h

#include "indexData.h"
#include "uniformFunction.h"
#include "vertexData.h"
#include "vertexDeclaration.h"

#include <memory>
#include <string>

namespace Fire
{
class Material;
class Texture;
class Renderable
{
public:
    Renderable(std::string const& name, std::unique_ptr<Material>&& material);

    ~Renderable();

    std::string GetName() const;

    void SetVertexDeclaration(VertexDeclaration const& vDecl);
    VertexDeclaration const& GetVertexDeclaration() const;

    VertexData& GetVertexData();
    IndexData& GetIndexData();

    Material* GetMaterial() const;

    void SetUniformFunction(UniformFunction func);
    UniformFunction GetUniformFunction() const;

    void AddTexture(Texture* tex);
    Texture* GetTexture() const;

private:
    std::string const m_name;
    VertexDeclaration m_vDecl;
    VertexData m_vData;
    IndexData m_iData;
    UniformFunction m_uniformFunction;
    Texture* m_texture;
    std::unique_ptr<Material> m_material;
};
} // namespace Fire

#endif // fire_renderable_h
