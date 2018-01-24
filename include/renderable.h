#ifndef blocks_renderable_h
#define blocks_renderable_h

#include <GL/glew.h>
#include <string>
#include <functional>
#include <vector>

namespace blocks
{
    class Material;
    class VertexDeclaration;
    class Texture;

    class Renderable
    {
    public:
        Renderable(std::string const name, VertexDeclaration const& vertexDecl
            , void* vertexData, size_t dataSize, std::vector<unsigned int> const& indexData, Material const* material, Texture* texture
            , std::function<void(void)> const& uniformFunction);

        std::string GetName() const;
        
        void Render();
        
    private:
        std::string const m_name;
        Material const* m_material;
        Texture* m_texture;
        std::function<void(void)> m_uniformFunction;
        GLuint m_vbo;
        GLuint m_vao;
        GLuint m_ibo;
        unsigned int m_numIndices;
    };
}

#endif // blocks_renderable_h
