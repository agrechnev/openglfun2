#version 330 core

// This version of Material icludes a texture for diffuse+specular

struct MaterialT {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
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
in vec2 pTexCoord;

out vec4 color;

uniform vec3 uCamPos;
uniform MaterialT uMaterialT;
uniform Light uLight;

//===============================

void main(){

    // Ambient 
    vec3 texA = vec3(texture(uMaterialT.ambient, pTexCoord));
    vec3 ambient = uLight.ambient * texA;

    // Diffuse
    vec3 texD = vec3(texture(uMaterialT.diffuse, pTexCoord));
    vec3 norm = normalize(pNorm);
    vec3 lightDir = normalize(uLight.position - pFragPos);
    float diff = max(dot(norm, lightDir), 0.0f);

    vec3 diffuse = uLight.diffuse * diff * texD;
    
    // Specular Texture 
    vec3 texS = vec3(texture(uMaterialT.specular, pTexCoord));
    
    // Specular
    vec3 viewDir = normalize(uCamPos - pFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = uLight.specular * spec * texS;
    
    // Emission
    vec3 emission = vec3(texture(uMaterialT.emission, pTexCoord));
    
    // Result : ambient + diffuse + specular + emission
    vec3 result = ambient + diffuse + specular + emission;
    color = vec4(result, 1.0f);
}
