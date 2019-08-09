#version 440

uniform sampler2D tex;
uniform vec3 LightPos;

in vec2 texVS;
in vec3 normalVS;
in vec3 posVS;


out vec4 color;

void main()
{
    color = texture(tex, texVS).rgba;
    if (color.a <= 0.5) {
        discard;
    }

    vec3 normal = normalize(normalVS);

    vec3 L = normalize(LightPos - posVS);
    float NDotL = max(dot(normal, L), 0.0);

    vec4 col = vec4(0.1) + color;
    color = clamp(col * 0.2 + col * 0.8 * NDotL, 0.0, 1.0);
    color.w = 1.0;
}


