#version 440

in vec3 posVS;
out vec4 color;

void main()
{
    vec2 coord = posVS.xz;
    vec2 frac = abs(fract(coord - 0.5) - 0.5);
    vec2 val = smoothstep(0.0, 1.0, frac * 20.0 * (0.5 - fwidth(coord)));
    vec4 purple = vec4(1.0, 0.13, 0.47, 1.0);
    vec4 blue = vec4(0.02, 0.0, 0.37, 1.0);
    color = mix(purple, blue, val.x * val.y);
}