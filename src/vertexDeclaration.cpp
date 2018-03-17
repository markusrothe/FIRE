#include "vertexDeclaration.h"

#include <algorithm>

namespace blocks
{
    VertexDeclarationSection::VertexDeclarationSection(std::string const& attributeName, unsigned int numElements, unsigned int stride, unsigned int offset)
        : m_attributeName(attributeName)
        , m_numElements(numElements)
        , m_stride(stride)
        , m_offset(offset)
    {

    }

    void VertexDeclaration::AddSection(std::string const& name, unsigned int numElements, unsigned int stride, unsigned int offset)
    {
        m_sections.push_back(VertexDeclarationSection(name, numElements, stride, offset));
    }

    std::vector<VertexDeclarationSection> const& VertexDeclaration::GetSections() const
    {
        return m_sections;
    }

    std::vector<VertexDeclarationSection>::const_iterator const VertexDeclaration::GetSection(std::string const& name) const
    {
        return std::find_if(
            std::begin(m_sections), std::end(m_sections),
            [&name](auto const& section)
            {
                return section.m_attributeName.compare(name) == 0;
            });
    }

} // namespace blocks
