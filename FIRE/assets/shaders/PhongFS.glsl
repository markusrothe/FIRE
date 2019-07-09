#version 440

uniform vec3 LightPos;

in vec3 posVS;
in vec3 normalVS;

out vec4 color;

void main()
{
    vec3 normal = normalize(normalVS);

    vec3 l = normalize(LightPos - posVS);
    float nDotL = dot(normal, l);
    if(nDotL < 0.)
    {
        nDotL = 0.;
    }

    vec3 ambient = vec3(.1, .1, .1);
    vec3 diffuse = 0.7 * vec3(nDotL);

    float distanceToLight = length(LightPos - posVS);
    float attenuation = 1. / (1. + .001 * pow(distanceToLight, 2));

    vec3 gamma = vec3(1. / 2.2);

    color = vec4(ambient, 1.) + attenuation * vec4(diffuse, 1.);
    color = vec4(pow(color.xyz, gamma), 1.);
}
