#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 color;
layout (location=2) in vec2 texCoord;

out vec3 pColor;
out vec2 pTexCoord;

uniform mat4 uTran;

void main(){
    gl_Position = uTran*vec4(pos, 1.0f);
    pColor=color;
    pTexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}
