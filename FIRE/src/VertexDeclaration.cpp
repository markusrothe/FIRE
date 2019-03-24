#include <FIRE/VertexDeclaration.h>

namespace FIRE
{
VertexDeclarationSection::VertexDeclarationSection(
    unsigned int size, unsigned int offset, unsigned int stride)
    : size(size)
    , offset(offset)
    , stride(stride)
{
}

void VertexDeclaration::AddSection(
    std::string name, unsigned int size, unsigned int offset,
    unsigned int stride)
{
    m_sections.insert(
        std::make_pair(name, VertexDeclarationSection(size, offset, stride)));
}

VertexDeclaration::VertexDeclarationMap VertexDeclaration::GetSections() const
{
    return m_sections;
}

} // namespace FIRE
