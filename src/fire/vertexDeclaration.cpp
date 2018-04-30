#include "vertexDeclaration.h"
#include <algorithm>


namespace Fire
{
    VertexDeclarationSection::VertexDeclarationSection(
        std::string const& name, unsigned int numElements
        , unsigned int stride, unsigned int offset)
        : m_attributeName(name)
        , m_numElements(numElements)
        , m_stride(stride)
        , m_offset(offset)
    {
        
    }
    
    void VertexDeclaration::AddSection(std::string const& name, unsigned int numElements
                                       , unsigned int stride, unsigned int offset)
    {
        m_sections.emplace_back(name, numElements, stride, offset);
    }

    VertexDeclarationSections const& VertexDeclaration::GetSections() const
    {
        return m_sections;
    }

    VertexDeclarationSections::const_iterator const
    VertexDeclaration::GetSection(std::string const& name) const
    {
        return std::find_if(
            std::cbegin(m_sections), std::cend(m_sections),
            [&name](auto const& section)
            {
                return section.m_attributeName.compare(name) == 0;
            });
        
    }
    
}
