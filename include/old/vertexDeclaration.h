#ifndef blocks_vertexDeclaration_h
#define blocks_vertexDeclaration_h

#include <vector>
#include <string>
#include <tuple>

namespace blocks
{
    struct VertexDeclarationSection
    {
        VertexDeclarationSection(std::string const& attributeName, unsigned int numElements, unsigned int stride, unsigned int offset);

        std::string m_attributeName;
        unsigned int m_numElements;
        unsigned int m_stride;
        unsigned int m_offset;
    };

    class VertexDeclaration
    {
    public:
        void AddSection(std::string const& name, unsigned int numElements, unsigned int stride, unsigned int offset);

        std::vector<VertexDeclarationSection> const& GetSections() const;
        
        std::vector<VertexDeclarationSection>::const_iterator const GetSection(std::string const& name) const;

        
    private:

        std::vector<VertexDeclarationSection> m_sections;
    };
}

#endif // blocks_vertexDeclaration_h
