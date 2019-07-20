#version 440

layout(location = 0) in vec3 vPos;

uniform mat4 VP;
uniform mat4 M;

out vec3 posVS;

void main()
{
    gl_Position = VP * M * vec4(vPos, 1.0);
    posVS = (M * vec4(vPos, 1.0)).xyz;
}
