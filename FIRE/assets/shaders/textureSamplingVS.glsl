#version 440

layout(location = 0) in vec3 vPos;
layout(location = 2) in vec2 vUV;

uniform mat4 VP;
uniform mat4 M;

out vec2 texVS;

void main()
{
    gl_Position = VP * M * vec4(vPos, 1.0);
    texVS = vUV;
}
