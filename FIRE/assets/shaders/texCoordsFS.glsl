#version 440

uniform vec3 LightPos;

in vec3 posVS;
in vec3 normalVS;
in vec2 texVS;

out vec4 color;

void main()
{
    color = vec4(texVS.x, 0.0, texVS.y, 1.0);
}
