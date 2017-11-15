#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 norm;

out vec3 pNorm;
out vec3 pFragPos; 

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main(){
    pNorm = mat3(uView*uModel)*norm; // For now
    vec4 tmp = uView*uModel*vec4(pos, 1.0f);
    pFragPos = vec3(tmp);
    gl_Position = uProj*tmp;
}
