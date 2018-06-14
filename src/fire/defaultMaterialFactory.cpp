#include "defaultMaterialFactory.h"
#include "material.h"
#include "glslShader.h"
#include "glslShaderCompiler.h"
#include <utility>

namespace Fire
{
	auto const vertexShaderCode = "";
	auto const fragmentShaderCode = "";

	std::unique_ptr<Material> CreateDefaultMaterial()
	{
		GLSLShaderCompiler const vertexShaderCompiler(vertexShaderCode, ShaderCompiler::ShaderType::VERTEX_SHADER);
		GLSLShaderCompiler const fragmentShaderCompiler(fragmentShaderCode, ShaderCompiler::ShaderType::FRAGMENT_SHADER);

		//GLSLShaderLinker const shaderLinker(vertexShaderCompiler.GetCompileOutput(), fragmentShaderCompiler.GetCompileOutput());

		//auto shader = std::make_unique<GLSLShader>(shaderLinker.GetLinkOutput());
		auto shader = std::make_unique<GLSLShader>("shader");
		return std::make_unique<Material>("simple", std::move(shader));
	}
} // namespace Fire