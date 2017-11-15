#version 330 core

// This version of Material icludes a texture for diffuse+specular

struct MaterialT {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
    int flags;
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
    vec3 ambient = vec3(0.0f);
    if ( (uMaterialT.flags & 1) > 0) {
        vec3 texA = vec3(texture(uMaterialT.ambient, pTexCoord));
        ambient = uLight.ambient * texA;
    }
        

    // Diffuse
    vec3 diffuse = vec3(0.0f);
    
    vec3 norm = normalize(pNorm);
    vec3 lightDir = normalize(uLight.position - pFragPos);
    if ( (uMaterialT.flags & 2) > 0) {
        vec3 texD = vec3(texture(uMaterialT.diffuse, pTexCoord));
        float diff = max(dot(norm, lightDir), 0.0f);
        diffuse = uLight.diffuse * diff * texD;
    }
    
    // Specular
    vec3 specular = vec3(0.0f);
    
    if ( (uMaterialT.flags & 4) > 0) {
        vec3 texS = vec3(texture(uMaterialT.specular, pTexCoord)); // Texture
        vec3 viewDir = normalize(uCamPos - pFragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        specular = uLight.specular * spec * texS;
    }
    
    // Emission
    vec3 emission = vec3(0.0f);
    
    if ( (uMaterialT.flags & 8) > 0) {
        emission = vec3(texture(uMaterialT.emission, pTexCoord));
    }
    
    // Result : ambient + diffuse + specular + emission
    vec3 result = ambient + diffuse + specular + emission;
    color = vec4(result, 1.0f);
}
