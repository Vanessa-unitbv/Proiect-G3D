#version 330 core

in vec2 TexCoord;
in vec3 fragPos;
in vec3 normal;

out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 viewPos;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light1;
uniform Light light2;
uniform Light light3;

vec3 calculateLighting(Light light, vec3 normal, vec3 fragPos, vec3 texColor) {
    vec3 ambient = light.ambient * texColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texColor;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec;

    return ambient + diffuse + specular;
}

void main() {
    vec4 texColor = texture(texture1, TexCoord);
    
    vec3 result = vec3(0.0);
    
    result += calculateLighting(light1, normal, fragPos, texColor.rgb);
    result += calculateLighting(light2, normal, fragPos, texColor.rgb);
    result += calculateLighting(light3, normal, fragPos, texColor.rgb);

    FragColor = vec4(result, 1.0);
}
