#ifndef fire_vertexdeclaration_h
#define fire_vertexdeclaration_h

#include <string>
#include <vector>

namespace Fire
{
    struct VertexDeclarationSection
    {
        VertexDeclarationSection(std::string const& name, unsigned int numElements
                                 , unsigned int stride, unsigned int offset);

        std::string const m_attributeName;
        unsigned int m_numElements;
        unsigned int m_stride;
        unsigned int m_offset;
    };

    typedef std::vector<VertexDeclarationSection> VertexDeclarationSections;
    
    class VertexDeclaration
    {
    public:                
        void AddSection(std::string const& attributeName
                        , unsigned int size
                        , unsigned int stride
                        , unsigned int offset);
                
        VertexDeclarationSections const& GetSections() const;

        VertexDeclarationSections::const_iterator const GetSection(
            std::string const& name) const;
        
        
    private:
        VertexDeclarationSections m_sections;
    };
} // namespace Fire

#endif // fire_vertexdeclaration_h
