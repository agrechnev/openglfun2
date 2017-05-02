#version 330 core

layout (location=0) in vec3 pos;
layout (location=2) in vec2 texCoord;

out vec2 pTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main(){
    gl_Position = uProj*uView*uModel*vec4(pos, 1.0f);
    pTexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}
