#include "renderable.h"
#include "vertexDeclaration.h"
#include "material.h"
#include "texture.h"
#include <iostream>

namespace blocks
{
    namespace
    {
        GLuint GenerateVertexBuffer(void* data, size_t dataSize)
        {
            GLuint vbo = 0;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
            
            return vbo;
        }

        GLuint GenerateIndexBuffer(std::vector<unsigned int> const& indexData)
        {
            GLuint ibo = 0;
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), &(indexData[0]), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            return ibo;
        }

        void BindShaderAttributes(VertexDeclaration const& vertexDecl, GLuint shaderID)
        {

            for (auto const& vertexDeclSection : vertexDecl.GetSections())
            {
                auto attribLocation = glGetAttribLocation(shaderID, vertexDeclSection.m_attributeName.c_str());
                glEnableVertexAttribArray(attribLocation);
                glVertexAttribPointer(attribLocation, vertexDeclSection.m_numElements, GL_FLOAT
                                      , GL_FALSE, vertexDeclSection.m_stride, (const GLvoid*) vertexDeclSection.m_offset);
            }
        }

    } // namespace

    Renderable::Renderable(std::string const name, VertexDeclaration const& vertexDecl
                           , void* vertexData, size_t dataSize, std::vector<unsigned int> const& indexData
                           , Material const* material, Texture* texture
                           , std::function<void(void)> const& uniformFunction)
        : m_name(name)
        , m_material(material)
        , m_texture(texture)
        , m_uniformFunction(uniformFunction)
        , m_vbo(0)
        , m_vao(0)
        , m_ibo(0)
        , m_numIndices(indexData.size())
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        m_vbo = GenerateVertexBuffer(vertexData, dataSize);
        BindShaderAttributes(vertexDecl, m_material->GetShaderID());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        m_ibo = GenerateIndexBuffer(indexData);
    }

    std::string Renderable::GetName() const
    {
        return m_name;
    }

    void Renderable::Render()
    {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        
        m_material->Bind();

        if(m_texture) m_texture->Bind();
        
        if(m_uniformFunction) m_uniformFunction();
        
        glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

        if(m_texture) m_texture->Unbind();
        m_material->Unbind();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
} // namespace blocks
