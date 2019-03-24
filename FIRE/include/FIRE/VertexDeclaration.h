#ifndef FIRE_VertexDeclaration_h
#define FIRE_VertexDeclaration_h
#include <string>
#include <unordered_map>
namespace FIRE
{
struct VertexDeclarationSection
{
    explicit VertexDeclarationSection(
        unsigned int size, unsigned int offset, unsigned int stride);

    unsigned int size;
    unsigned int offset;
    unsigned int stride;
};

class VertexDeclaration
{
public:
    using VertexDeclarationMap =
        std::unordered_map<std::string, VertexDeclarationSection>;

    void AddSection(
        std::string name, unsigned int size, unsigned int offset,
        unsigned int stride);

    VertexDeclarationMap GetSections() const;

private:
    VertexDeclarationMap m_sections;
};
} // namespace FIRE

#endif // !FIRE_VertexDeclaration_h
