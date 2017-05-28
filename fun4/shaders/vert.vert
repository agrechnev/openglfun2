#version 330 core

layout (location=0) in vec3 lPos;
layout (location=1) in vec3 lNorm;

out vec3 pNorm;
out vec3 pFragPos; 

uniform mat4 uCam;
uniform mat4 uModel;
uniform mat4 uNorm;

void main(){
    pNorm = mat3(uNorm)*lNorm;  // Normal
    vec4 tmp = uModel*vec4(lPos, 1.0f);  // Model position
    pFragPos = vec3(tmp);
    gl_Position = uCam*tmp;  // Camera
}
