#include "materialFactory.h"
#include "shaderCompiler.h"
#include "shaderLinker.h"
#include "material.h"

namespace Fire
{
	std::unique_ptr<Material> CreateMaterial(
		ShaderCompiler* vertexShaderCompiler,
		ShaderCompiler* fragmentShaderCompiler,
		ShaderLinker* shaderLinker)
	{
		if (!vertexShaderCompiler || !fragmentShaderCompiler || !shaderLinker)
		{
			return nullptr;
		}

		vertexShaderCompiler->Compile();
		fragmentShaderCompiler->Compile();

		shaderLinker->Link();

		return std::make_unique<Material>("", nullptr);
	}
}