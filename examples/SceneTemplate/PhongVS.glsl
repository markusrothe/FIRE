#version 440

layout(location=0)in vec3 vPos;
layout(location=1)in vec3 vNormal;

uniform mat4 VP;
uniform mat4 M;

out vec3 posVS;
out vec3 normalVS;

void main()
{
    gl_Position = VP * M * vec4(vPos, 1.0);
    
    posVS = (M * vec4(vPos, 1.0)).xyz;
    normalVS = (M * vec4(normalize(vNormal), 1.0)).xyz;
}
