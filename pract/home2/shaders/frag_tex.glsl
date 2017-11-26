#version 330 core

in vec2 pTexCoord;

out vec4 color;

uniform sampler2D uTex1;

void main(){
    color = texture(uTex1, pTexCoord);
}
