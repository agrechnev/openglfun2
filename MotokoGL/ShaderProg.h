#pragma once
// By Oleksiy Grechnyev

#include <string>
#include <memory>

#include "./glheader.h"


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

    /// Create shader program from files
    static ShaderProg fromFiles(const std::string & vertexFileName, const std::string & fragmentFileName);

public: //==== Methods
    /// Use this shader prog
    void use() const{
        glUseProgram(prog);
    }

    /// Locate a uniform
    GLint loc(const std::string & uniformName) const{
        return glGetUniformLocation(prog, uniformName.c_str());
    }

    /// Set model and cam matrices (uniforms uModel, uCam)
    void setMat(const glm::mat4 & cam, const glm::mat4 & model){
        glUniformMatrix4fv(uCam, 1, GL_FALSE, value_ptr(cam));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, value_ptr(model));
    }

private: //==== Methods
    // Read a whole file as a string
    static std::shared_ptr<std::string> parseFile(const std::string & fileName);

private: //==== Fields
    /// The program's OpenGL id
    GLuint prog = 0;
    /// Uniforms
    GLint uModel, uCam;
};
}

