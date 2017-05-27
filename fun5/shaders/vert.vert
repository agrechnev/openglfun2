#version 330 core

layout (location=0) in vec3 lPos;
layout (location=1) in vec3 lNorm;
layout (location=2) in vec2 lTexCoord;

out vec3 pNorm;
out vec3 pFragPos; 
out vec2 pTexCoord;

uniform mat4 uCam;
uniform mat4 uModel;

void main(){
    pNorm = mat3(uModel)*lNorm;    // Norm transformed (No Scaling !!!)
    vec4 tmp = uModel*vec4(lPos, 1.0f); 
    pFragPos = vec3(tmp);   // Frag position
    gl_Position = uCam*tmp; // View position
    pTexCoord = vec2(lTexCoord.x, 1.0f - lTexCoord.y);  // Texture
}
