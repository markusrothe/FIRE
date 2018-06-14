#version 440

uniform mat4 MVP;

in vec4 vertex;

int main()
{
	glPosition = MVP * vertex;
}