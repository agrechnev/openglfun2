#version 330 core

in vec3 pNorm;

out vec4 color;

uniform vec3 uObjectC;
uniform vec3 uLightC;

void main(){
    float ambientStr = 0.1;
    vec3 ambient = ambientStr*uLightC;

    vec3 result = ambient*uObjectC;
    color = vec4(result, 1.0f);
}
