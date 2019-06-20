#ifndef FIRE_VertexDeclaration_h
#define FIRE_VertexDeclaration_h
#include <string>
#include <unordered_map>
namespace FIRE
{
struct VertexDeclarationSection
{
    explicit VertexDeclarationSection(size_t size, size_t offset);

    size_t size;
    size_t offset;
};

class VertexDeclaration
{
public:
    using VertexDeclarationMap = std::unordered_map<std::string, VertexDeclarationSection>;

    void AddSection(std::string name, size_t size, size_t offset);

    VertexDeclarationMap GetSections() const;

private:
    VertexDeclarationMap m_sections;
};
} // namespace FIRE

#endif // !FIRE_VertexDeclaration_h
