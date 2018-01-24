#include "vertexDeclaration.h"

namespace blocks
{
    VertexDeclarationSection::VertexDeclarationSection(std::string const attributeName, unsigned int numElements, unsigned int stride, unsigned int offset)
        : m_attributeName(attributeName)
        , m_numElements(numElements)
        , m_stride(stride)
        , m_offset(offset)
    {

    }

    void VertexDeclaration::AddSection(std::string name, unsigned int numElements, unsigned int stride, unsigned int offset)
    {
        m_sections.push_back(VertexDeclarationSection(name, numElements, stride, offset));
    }

    std::vector<VertexDeclarationSection> const& VertexDeclaration::GetSections() const
    {
        return m_sections;
    }

} // namespace blocks