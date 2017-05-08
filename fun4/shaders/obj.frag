#version 330 core

in vec3 pNorm;
in vec3 pFragPos;

out vec4 color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform vec3 uObjectC;
uniform vec3 uLightC;
uniform vec3 uLightPos;
uniform vec3 uCamPos;
uniform Material uMaterial;

void main(){
    // Ambient
    vec3 ambient = uLightC * (uMaterial.ambient);

    // Diffuse
    vec3 norm = normalize(pNorm);
    vec3 lightDir = normalize(uLightPos - pFragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    //float diff = abs(dot(norm, lightDir));
    
    vec3 diffuse = uLightC * (diff * uMaterial.diffuse);
    
    // Specular
    vec3 viewDir = normalize(uCamPos - pFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = uLightC *(spec * uMaterial.specular);
    
    // Result : ambient + diffuse
    vec3 result = (ambient + diffuse + specular) * uObjectC;
    color = vec4(result, 1.0f);
}
