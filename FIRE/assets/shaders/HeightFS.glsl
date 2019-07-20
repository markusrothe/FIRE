#version 440

in vec3 posVS;
out vec4 color;

void main()
{
    float height = posVS.y / 100.0f;
    vec4 blue = vec4(0.1, 0.1, 0.5, 1.0);
    vec4 green = vec4(0.0, 0.3, 0.0, 1.0);
    vec4 brown = vec4(0.8, 0.6, 0.4, 1.0);
    vec4 grey = vec4(0.9, 0.9, 0.9, 1.0);
    color = mix(blue, green, smoothstep(0.1, 0.15, height));
    color = mix(color, brown, smoothstep(0.15, 0.8, height));
    color = mix(color, grey, smoothstep(0.8, 1.0, height));
}