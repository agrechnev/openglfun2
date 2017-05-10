#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 pNorm;
in vec3 pFragPos;

out vec4 color;

uniform vec3 uCamPos;
uniform Material uMaterial;
uniform Light uLight;

//===============================

void main(){
    // Ambient
    vec3 ambient = uLight.ambient * uMaterial.ambient;

    // Diffuse
    vec3 norm = normalize(pNorm);
    vec3 lightDir = normalize(uLight.position - pFragPos);
    float diff = max(dot(norm, lightDir), 0.0f);

    vec3 diffuse = uLight.diffuse * (diff * uMaterial.diffuse);
    
    // Specular
    vec3 viewDir = normalize(uCamPos - pFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = uLight.specular *(spec * uMaterial.specular);
    
    // Result : ambient + diffuse + specular
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}
