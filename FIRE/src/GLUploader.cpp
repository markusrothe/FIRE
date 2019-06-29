#include "GLUploader.h"
#include <FIRE/Material.h>
#include <FIRE/Mesh.h>
#include <FIRE/MeshFactory.h>
#include <FIRE/Renderable.h>
#include <FIRE/VertexDeclaration.h>

#define BUFFER_OFFSET(i) ((void*)(std::uintptr_t)(i))

namespace FIRE
{
namespace
{
void SpecifyVertexAttributes(VertexDeclaration const& vDecl, GLuint shader)
{
    for(auto const& vertexDeclSection : vDecl.GetSections())
    {
        auto attribLocation = glGetAttribLocation(
            shader,
            vertexDeclSection.first.c_str());

        auto const stride = 0u;
        glEnableVertexAttribArray(attribLocation);
        glVertexAttribPointer(
            attribLocation,
            vertexDeclSection.second.size,
            GL_FLOAT,
            GL_FALSE,
            stride,
            BUFFER_OFFSET(vertexDeclSection.second.offset));
    }
}

void Write(std::vector<float> const& data, unsigned int offset)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, data.size() * sizeof(float), &data[0]);
}

GLuint UploadVertices(Mesh* mesh, GLuint shader)
{
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto const positions = mesh->PositionsAsArray();
    auto const normals = mesh->NormalsAsArray();

    auto bufferSize = (positions.size() + normals.size()) * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);

    if(!positions.empty())
    {
        Write(positions, 0u);
    }

    if(!normals.empty())
    {
        Write(normals, positions.size() * sizeof(float));
    }

    SpecifyVertexAttributes(mesh->GetVertexDeclaration(), shader);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

GLuint UploadIndices(std::vector<unsigned int> const& indices)
{
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    auto const indicesSize = indices.size() * sizeof(unsigned int);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indicesSize,
        &(indices[0]),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return ibo;
}

} // namespace

GLUploader::GLUploader(MeshFactory& meshFactory)
    : m_meshFactory(meshFactory)
{
}

GLVertexArrayObject GLUploader::Upload(Renderable const& renderable)
{
    auto const it = m_uploadedRenderables.find(renderable.name);
    if(it != m_uploadedRenderables.end())
    {
        return it->second;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Mesh* mesh = m_meshFactory.Lookup(renderable.mesh);
    if(!mesh)
    {
        return GLVertexArrayObject(0, 0, 0);
    }

    GLuint const vbo = UploadVertices(mesh, renderable.material.ShaderId());
    GLuint const ibo = UploadIndices(mesh->Indices());

    GLVertexArrayObject arrObj(vao, vbo, ibo);
    m_uploadedRenderables.insert(std::make_pair(renderable.name, arrObj));
    return arrObj;
}

} // namespace FIRE
