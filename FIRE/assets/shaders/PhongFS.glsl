#version 440

uniform vec3 LightPos;

in vec3 posVS;
in vec3 normalVS;

out vec4 color;

void main()
{
    vec3 normal = normalize(normalVS);

    vec3 L = abs(normalize(LightPos - posVS));
    float NDotL = max(dot(normal, L), 0.0);

    vec4 col = vec4(1.0);
    color = clamp(col * 0.2 + col * 0.8 * NDotL, 0.0, 1.0);
}
