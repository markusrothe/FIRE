#include "GLDrawAgent.h"
#include <FIRE/MeshManager.h>
#include <FIRE/Renderable.h>
#include <FIRE/glmfwd.h>
#include <any>

namespace FIRE
{
namespace
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
            auto const& uniformVal = std::any_cast<glm::mat4x4>(paramVal);
            glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(uniformVal));
            break;
        }
        case ShaderParameterType::VEC3:
        {
            auto const& uniformVal = std::any_cast<glm::vec3>(paramVal);
            glUniform3fv(uniformLocation, 1, glm::value_ptr(uniformVal));
            break;
        }
        }
    }
}

GLenum MapPrimitiveType(MeshPrimitives primitives)
{
    switch(primitives)
    {
    case MeshPrimitives::Points:
        return GL_POINTS;
    case MeshPrimitives::Lines:
        return GL_LINES;
    case MeshPrimitives::Triangles:
        return GL_TRIANGLES;
    default:
        assert(false);
        return GL_POINTS;
    }
}

} // namespace
GLDrawAgent::GLDrawAgent(MeshManager& meshManager)
    : m_meshManager(meshManager)
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

    auto mesh = m_meshManager.Lookup3D(renderable.mesh);
    if(mesh)
    {
        glDrawElements(MapPrimitiveType(renderable.mesh.type.primitives), static_cast<GLsizei>(mesh->Indices().size()), GL_UNSIGNED_INT, 0);
    }

    glUseProgram(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLDrawAgent::ToggleWireframe()
{
    static bool on = false;

    if(on)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    on = !on;
}

} // namespace FIRE
