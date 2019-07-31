#include "GLMaterialBinder.h"
#include <FIRE/Material.h>
#include <FIRE/glmfwd.h>
#include <glad/glad.h>
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
} // namespace
void GLMaterialBinder::Bind(Material const& material)
{
    glUseProgram(material.ShaderId());
    SetShaderUniforms(material.ShaderId(), material.GetShaderParameters());
}

void GLMaterialBinder::Release()
{
    glUseProgram(0);
}
} // namespace FIRE
