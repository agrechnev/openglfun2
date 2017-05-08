#version 330 core

layout (location=0) in vec3 lPos;
layout (location=1) in vec3 lNorm;

out vec4 pColor;

uniform mat4 uCam;
uniform mat4 uModel;

uniform vec3 uObjectC;
uniform vec3 uLightC;
uniform vec3 uLightPos;
uniform vec3 uCamPos;

void main(){
    vec3 norm = normalize(mat3(uModel)*lNorm);
    vec4 tmp = uModel*vec4(lPos, 1.0f);
    vec3 fragPos = vec3(tmp);
    gl_Position = uCam*tmp;
    
    // Set lighting
    // Ambient
    float ambientStr = 0.1;
    vec3 ambient = ambientStr*uLightC;

    // Diffuse
    float diffuseStr = 0.5;
    vec3 lightDir = normalize(uLightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    
    vec3 diffuse = diffuseStr * diff * uLightC;
    
    // Specular
    float specularStr = 0.5f;
    vec3 viewDir = normalize(uCamPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStr * spec * uLightC;
    
    // Result : ambient + diffuse + specular
    vec3 result = (ambient + diffuse + specular) * uObjectC;
    pColor = vec4(result, 1.0f);
}
