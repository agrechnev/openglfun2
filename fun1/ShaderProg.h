#pragma once
// By Oleksiy Grechnyev

// OpenGL Headers
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW (after GLEW)
#include <GLFW/glfw3.h>

namespace MotokoGL{
/// Shader program and compiling shaders
class ShaderProg
{
private: //==== Constructors ===
    /// Default private
    ShaderProg() {}

public: //==== Static factory methods
    /// Create shader program from memory strings
    static ShaderProg fromMem(const GLchar *vertexSource, const GLchar *fragmentSource);

public: //==== Methods
    // Use this shader prog
    void use(){
        glUseProgram(prog);
    }

private: //==== Fields
    GLuint prog = 0; // The program's OpenGL id
};
}

