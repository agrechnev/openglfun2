#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 norm;

out vec3 pNorm;

uniform mat4 uCam;
uniform mat4 uModel;

void main(){
    pNorm = norm;
    gl_Position = uCam*uModel*vec4(pos, 1.0f);
}
