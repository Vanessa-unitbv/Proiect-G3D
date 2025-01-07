#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

uniform Light light1;
uniform Light light2;
uniform Light light3;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoord));
    vec3 specular = light.specular * spec * vec3(0.5);
    
    return (ambient + diffuse + specular) * attenuation;
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = vec3(0.0);
    result += CalcPointLight(light1, norm, FragPos, viewDir);
    result += CalcPointLight(light2, norm, FragPos, viewDir);
    result += CalcPointLight(light3, norm, FragPos, viewDir);
    
    FragColor = vec4(result, 1.0);
}