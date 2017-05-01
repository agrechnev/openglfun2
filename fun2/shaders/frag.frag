#version 330 core

in vec3 pColor;
out vec4 color;

void main(){
    color = vec4(pColor, 1.0f);
}
