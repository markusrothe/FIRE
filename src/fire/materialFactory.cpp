#include "materialFactory.h"
#include "material.h"
#include "shaderCompiler.h"
#include "shaderLinker.h"

namespace Fire
{
std::unique_ptr<Material> CreateMaterial(
    ShaderCompiler* vertexShaderCompiler,
    ShaderCompiler* fragmentShaderCompiler, ShaderLinker* shaderLinker)
{
    if(!vertexShaderCompiler || !fragmentShaderCompiler || !shaderLinker)
    {
        return nullptr;
    }

    vertexShaderCompiler->Compile();
    fragmentShaderCompiler->Compile();

    shaderLinker->Link();

    return std::make_unique<Material>("", nullptr);
}
} // namespace Fire