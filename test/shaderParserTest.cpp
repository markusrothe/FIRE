#include "fire/shaderParser.h"

#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <string>
#include <algorithm>
#include <utility>

namespace
{
	std::string const vertexShaderCode =
		"#version 440 \n"
		"uniform mat4 MVP;\n"
		"(layout location = 1) in vec4 vertex;\n"
		"(layout location = 2) in vec4 color; \n"
		"int main()\n"
		"{\n"
		"	glPosition = MVP * vertex;\n"
		"}\n";

	class ShaderParserTest : public ::testing::Test
	{
	public:
		ShaderParserTest()
			: m_parser(vertexShaderCode)
		{

		}
	protected:
		Fire::ShaderParser m_parser;
	};

	void CheckParsedInputVariable(Fire::ShaderParser::InputLayoutMap map, int layoutLocation, std::string const& name)
	{
		auto expectedInput = std::make_pair(layoutLocation, name);

		auto const findIt = std::find_if(std::cbegin(map), std::cend(map),
			[&expectedInput](std::pair<int, std::string> input) {
			return input.first == expectedInput.first && input.second == expectedInput.second;
		});

		EXPECT_NE(findIt, std::cend(map));
	}

} // namespace

TEST_F(ShaderParserTest, ParsesShaderCodeNonDestructible)
{
	EXPECT_EQ(m_parser.GetCode(), vertexShaderCode);
}

TEST_F(ShaderParserTest, ParsesInputVariables)
{
	auto const expectedInput = std::make_pair(1, std::string("vertex"));

	auto const inputs = m_parser.GetInputs();
	CheckParsedInputVariable(inputs, 1, "vertex");
	//CheckParsedInputVariable(inputs, 2, "color"); TODO: Regex parsing einbauen 
}

TEST_F(ShaderParserTest, ParsesUniformVariables)
{
	auto const uniforms = m_parser.GetUniforms(); // TODO: Regex parsing einbauen

	ASSERT_EQ(uniforms.size(), 1u);
	EXPECT_EQ(uniforms[0], std::string("MVP"));
}