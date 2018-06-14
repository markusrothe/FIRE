#include "defaultMaterialFactory.h"
#include "materialFactory.h"
#include "material.h"
#include "glslShader.h"
#include "glslShaderCompiler.h"
#include "glslShaderLinker.h"
#include <utility>

namespace Fire
{
	auto const vertexShaderCode = "";
	auto const fragmentShaderCode = "";

	std::unique_ptr<Material> CreateDefaultMaterial()
	{
		GLSLShaderCompiler vertexShaderCompiler(vertexShaderCode, ShaderCompiler::ShaderType::VERTEX_SHADER);
		GLSLShaderCompiler fragmentShaderCompiler(fragmentShaderCode, ShaderCompiler::ShaderType::FRAGMENT_SHADER);

		//GLSLShaderLinker const shaderLinker(vertexShaderCompiler.GetCompileOutput(), fragmentShaderCompiler.GetCompileOutput());
		GLSLShaderLinker shaderLinker;

		return CreateMaterial(&vertexShaderCompiler, &fragmentShaderCompiler, &shaderLinker);
	}
} // namespace Fire