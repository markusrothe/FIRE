#include "GLDrawAgent.h"
#include <FIRE/MeshFactory.h>
#include <FIRE/Renderable.h>
#include <any>
namespace FIRE
{
void SetShaderUniforms(GLuint shader, std::map<std::string, std::pair<ShaderParameterType, std::any>> const& params)
{
    for(auto const& param : params)
    {
        auto const& name = param.first;
        auto const& paramType = param.second.first;
        auto const& paramVal = param.second.second;
        auto const uniformLocation = glGetUniformLocation(shader, name.c_str());

        switch(paramType)
        {
        case ShaderParameterType::MAT4x4:
        {
            auto const& uniformVal = std::any_cast<Matrix4x4>(paramVal);
            glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, uniformVal.Raw().data());
            break;
        }
        case ShaderParameterType::VEC3:
        {
            auto const& uniformVal = std::any_cast<Vector3>(paramVal);
            glUniform3fv(uniformLocation, 1, uniformVal.Raw().data());
            break;
        }
        }
    }
}

GLDrawAgent::GLDrawAgent(MeshFactory& meshFactory)
    : m_meshFactory(meshFactory)
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GLDrawAgent::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDrawAgent::Draw(Renderable const& renderable, GLVertexArrayObject arrObj)
{
    glBindVertexArray(arrObj.m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arrObj.m_ibo);
    auto const shader = renderable.material.ShaderId();
    glUseProgram(shader);

    SetShaderUniforms(shader, renderable.material.GetShaderParameters());

    Mesh* mesh = m_meshFactory.Lookup(renderable.mesh);
    if(mesh)
    {
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->Indices().size()), GL_UNSIGNED_INT, 0);
    }

    glUseProgram(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

} // namespace FIRE
