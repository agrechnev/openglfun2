#include "ShaderProg.h"

#include "./fatal.h"

namespace MotokoGL{

ShaderProg ShaderProg::fromMem(const GLchar *vertexSource, const GLchar *fragmentSource)
{
    ShaderProg newProg;
    GLuint & prog = newProg.prog;

    // Create shaders and Compile
    // Vertex
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        fatal2("Cannot compile vertex shader", infoLog);
    }

    // Fragment
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        fatal2("Cannot compile fragment shader", infoLog);
    }

    // Shader program
    prog = glCreateProgram();
    glAttachShader(prog, vertexShader);
    glAttachShader(prog, fragmentShader);
    glLinkProgram(prog);

    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(prog, 512, nullptr, infoLog);
        fatal2("Cannot link shader program", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return newProg;
}

}
