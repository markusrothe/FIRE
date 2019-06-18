#version 440

layout(location=0)in vec3 vPos;
layout(location=1)in vec3 vNormal;

uniform mat4 MVP;

out vec3 posVS;
out vec3 normalVS;

void main()
{
    gl_Position=MVP*vec4(vPos.xyz,1.);
    
    posVS=vPos;
    normalVS=vNormal;
}