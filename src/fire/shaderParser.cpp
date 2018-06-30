#include "shaderParser.h"
#include <regex>

namespace Fire
{
    ShaderParser::ShaderParser(std::string const& code)
	: m_code(code)
    {

    }

    std::string ShaderParser::GetCode() const
    {
	return m_code;
    }

    ShaderParser::InputLayoutMap ShaderParser::GetInputs() const
    {
	InputLayoutMap inputLayout;
	inputLayout[1] = std::string("vertex");
	return inputLayout;
    }

    ShaderParser::Uniforms ShaderParser::GetUniforms() const
    {
	Uniforms uniforms;
	uniforms.push_back("MVP");
	return uniforms;
    }
} // namespace Fire
