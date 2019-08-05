#version 440

in vec2 texVS;
uniform sampler2D tex;

out vec4 color;

void main()
{
    color = vec4(vec3(texture(tex, texVS).r), 1.0);
}