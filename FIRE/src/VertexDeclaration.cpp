#include <FIRE/VertexDeclaration.h>

namespace FIRE
{
VertexDeclarationSection::VertexDeclarationSection(uint32_t size, uint32_t offset)
    : size(size)
    , offset(offset)
{
}

void VertexDeclaration::AddSection(std::string name, uint32_t size, uint32_t offset)
{
    m_sections.insert(std::make_pair(name, VertexDeclarationSection(size, offset)));
}

VertexDeclaration::VertexDeclarationMap VertexDeclaration::GetSections() const
{
    return m_sections;
}

} // namespace FIRE
