#include "GLVertexLayoutFactory.h"
#include "GLVertexLayout.h"
#include <FIRE/Mesh3D.h>
#include <FIRE/Renderable.h>
#include <glad/glad.h>
namespace FIRE
{

VertexLayout& GLVertexLayoutFactory::CreateStaticIndexedLayout(Renderable const& renderable)
{
    auto const it = m_cache.find(renderable.name);
    if(it != m_cache.end())
    {
        return *(it->second);
    }

    auto layout = std::make_unique<GLVertexLayout>(DrawMode::INDEXED);

    auto mesh = renderable.mesh;
    auto positions = mesh->Positions();
    auto normals = mesh->Normals();
    auto uvs = mesh->UVs();

    auto const positionsSize = positions.size() * sizeof(positions[0]);
    auto const normalsSize = normals.size() * sizeof(normals[0]);
    auto const uvsSize = uvs.size() * sizeof(uvs[0]);

    layout->BufferData(positionsSize + normalsSize + uvsSize, nullptr);

    if(!positions.empty())
    {
        layout->BufferSubData(0u, positionsSize, reinterpret_cast<void*>(&positions[0]));
    }

    if(!normals.empty())
    {
        layout->BufferSubData(positionsSize, normalsSize, reinterpret_cast<void*>(&normals[0]));
    }

    if(!uvs.empty())
    {
        layout->BufferSubData(positionsSize + normalsSize, uvsSize, reinterpret_cast<void*>(&uvs[0]));
    }

    for(auto const& vertexDeclSection : mesh->GetVertexDeclaration().GetSections())
    {
        layout->AddVertexAttribute(
            glGetAttribLocation(renderable.material.ShaderId(), vertexDeclSection.first.c_str()),
            vertexDeclSection.second.size,
            vertexDeclSection.second.offset);
    }

    auto indices = renderable.mesh->Indices();
    auto const indicesSize = indices.size() * sizeof(unsigned int);
    layout->BufferIndexData(indicesSize, reinterpret_cast<void*>(&indices[0]));

    auto& retVal = *layout;
    m_cache.insert(std::make_pair(renderable.name, std::move(layout)));

    return retVal;
}
VertexLayout& GLVertexLayoutFactory::CreateDynamicLayout(TextOverlay const& overlay)
{
    auto const it = m_cache.find(overlay.name);
    if(it != m_cache.end())
    {
        return *(it->second);
    }

    auto layout = std::make_unique<GLVertexLayout>(DrawMode::NON_INDEXED);
    layout->BufferData(sizeof(float) * 6 * 4, nullptr);

    layout->BindLayout();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    layout->ReleaseLayout();

    auto& retVal = *layout;
    m_cache.insert(std::make_pair(overlay.name, std::move(layout)));

    return retVal;
}
} // namespace FIRE
