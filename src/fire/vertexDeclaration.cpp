#include "vertexDeclaration.h"
#include "findByName.h"
#include <algorithm>
#include <functional>

namespace Fire
{
VertexDeclarationSection::VertexDeclarationSection()
    : m_attributeName("")
    , m_numElements(0)
    , m_stride(0)
    , m_offset(0)
{
}

VertexDeclarationSection::VertexDeclarationSection(
    std::string const& name, unsigned int numElements, unsigned int stride,
    unsigned int offset)
    : m_attributeName(name)
    , m_numElements(numElements)
    , m_stride(stride)
    , m_offset(offset)
{
}

void VertexDeclaration::AddSection(
    std::string const& name, unsigned int numElements, unsigned int stride,
    unsigned int offset)
{
    m_sections.emplace_back(name, numElements, stride, offset);
}

VertexDeclarationSection
VertexDeclaration::GetSection(std::string const& name) const
{
    return FindByName(
        m_sections, name, [](auto section) { return section.m_attributeName; });
}

std::vector<VertexDeclarationSection> const&
VertexDeclaration::GetSections() const
{
    return m_sections;
}
} // namespace Fire
