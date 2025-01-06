#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform Material material;
uniform Light light1;
uniform Light light2;
uniform Light light3;

vec3 CalcLight(Light light)
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    return ambient;
}

void main()
{
    vec3 result = CalcLight(light1);
    result += CalcLight(light2);
    result += CalcLight(light3);
    result = result * 1.0;
    FragColor = vec4(result, 1.0);
}
