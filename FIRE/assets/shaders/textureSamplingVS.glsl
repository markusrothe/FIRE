#version 440

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

uniform mat4 VP;
uniform mat4 M;

out vec2 texVS;
out vec3 normalVS;
out vec3 posVS;

void main()
{
    gl_Position = VP * M * vec4(vPos, 1.0);
    posVS = (M * vec4(vPos, 1.0)).xyz;
    normalVS = (M * vec4(normalize(vNormal), 1.0)).xyz;
    texVS = vUV;

}
