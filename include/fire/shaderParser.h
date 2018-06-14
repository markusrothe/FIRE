#ifndef fire_shaderparser_h
#define fire_shaderparser_h

#include <string>
#include <unordered_map>

namespace Fire
{
	class ShaderParser
	{	
	public:

		typedef std::unordered_map<int, std::string> InputLayoutMap;
		typedef std::vector<std::string> Uniforms;

		explicit ShaderParser(std::string const& code);

		std::string GetCode() const;
		InputLayoutMap GetInputs() const;
		Uniforms GetUniforms() const;

	private:
		std::string m_code;
	};
}

#endif // fire_shaderparser_h
