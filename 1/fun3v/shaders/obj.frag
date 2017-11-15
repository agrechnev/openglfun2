#version 330 core

in vec3 pNorm;
in vec3 pFragPos;

out vec4 color;

uniform vec3 uObjectC;
uniform vec3 uLightC;
uniform vec3 uLightPos;
uniform vec3 uCamPos;

void main(){
    // Ambient
    float ambientStr = 0.1;
    vec3 ambient = ambientStr*uLightC;

    // Diffuse
    float diffuseStr = 0.5;
    vec3 norm = normalize(pNorm);
    vec3 lightDir = normalize(uLightPos - pFragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    
    vec3 diffuse = diffuseStr * diff * uLightC;
    
    // Specular
    float specularStr = 0.5f;
    vec3 viewDir = normalize(uCamPos - pFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStr * spec * uLightC;
    
    // Result : ambient + diffuse
    vec3 result = (ambient + diffuse + specular) * uObjectC;
    color = vec4(result, 1.0f);
}
