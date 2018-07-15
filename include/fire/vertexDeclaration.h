#ifndef fire_vertexdeclaration_h
#define fire_vertexdeclaration_h

#include <string>
#include <vector>

namespace Fire
{
struct VertexDeclarationSection
{
    VertexDeclarationSection();

    VertexDeclarationSection(
        std::string const& name, unsigned int numElements, unsigned int stride,
        unsigned int offset);

    std::string m_attributeName;
    unsigned int m_numElements;
    unsigned int m_stride;
    unsigned int m_offset;
};

class VertexDeclaration
{
public:
    void AddSection(
        std::string const& attributeName, unsigned int size,
        unsigned int stride, unsigned int offset);

    VertexDeclarationSection GetSection(std::string const& name) const;

    std::vector<VertexDeclarationSection> const& GetSections() const;

private:
    std::vector<VertexDeclarationSection> m_sections;
};
} // namespace Fire

#endif // fire_vertexdeclaration_h
