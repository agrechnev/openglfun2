#version 330 core

layout (location=0) in vec3 lPos;
layout (location=1) in vec3 lNorm;

out vec3 pNorm;
out vec3 pFragPos; 

uniform mat4 uCam;
uniform mat4 uModel;

void main(){
    pNorm = mat3(uModel)*lNorm;
    vec4 tmp = uModel*vec4(lPos, 1.0f);
    pFragPos = vec3(tmp);
    gl_Position = uCam*tmp;
}
