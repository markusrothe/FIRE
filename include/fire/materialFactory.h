#ifndef fire_materialfactory_h
#define fire_materialfactory_h

#include <memory>

namespace Fire
{
	class Material;
	class ShaderCompiler;
	class ShaderLinker;

	std::unique_ptr<Material> CreateMaterial(
		ShaderCompiler* vertexShaderCompiler,
		ShaderCompiler* fragmentShaderCompiler,
		ShaderLinker* shaderLinker);
} // namespace Fire

#endif