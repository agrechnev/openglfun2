#version 330 core

in vec2 pTexCoord;
in vec4 pColor;

out vec4 color;

uniform sampler2D uTex1;
uniform sampler2D uTex2;

void main(){
    color = vec4(1.0) - mix(texture(uTex1, pTexCoord), texture(uTex2, pTexCoord), 0.3)*pColor;
}
