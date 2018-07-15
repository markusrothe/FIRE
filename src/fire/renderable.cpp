#include "renderable.h"
#include "material.h"
#include "texture.h"

namespace Fire
{
Renderable::Renderable(
    std::string const& name, std::unique_ptr<Material>&& material)
    : m_name{name}
    , m_vDecl{}
    , m_vData{}
    , m_iData{}
    , m_uniformFunction([]() {})
    , m_texture{}
    , m_material{std::move(material)}
{
}

Renderable::~Renderable() {}

std::string Renderable::GetName() const { return m_name; }

void Renderable::SetVertexDeclaration(VertexDeclaration const& vDecl)
{
    m_vDecl = vDecl;
}

VertexDeclaration const& Renderable::GetVertexDeclaration() const
{
    return m_vDecl;
}

VertexData& Renderable::GetVertexData() { return m_vData; }

IndexData& Renderable::GetIndexData() { return m_iData; }

Material* Renderable::GetMaterial() const { return m_material.get(); }

void Renderable::SetUniformFunction(UniformFunction func)
{
    m_uniformFunction = func;
}

UniformFunction Renderable::GetUniformFunction() const
{
    return m_uniformFunction;
}

void Renderable::AddTexture(Texture* tex) { m_texture = tex; }

Texture* Renderable::GetTexture() const { return m_texture; }
} // namespace Fire
