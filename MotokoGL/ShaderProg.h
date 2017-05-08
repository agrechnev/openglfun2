#pragma once
// By Oleksiy Grechnyev

#include <string>
#include <memory>

#include "./Material.h"
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

    /// Set cam and model  matrices (uniforms uCam, uModel)
    void setMat(const glm::mat4 & cam, const glm::mat4 & model){
        glUniformMatrix4fv(uCam, 1, GL_FALSE, value_ptr(cam));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, value_ptr(model));
    }

    /// Set model, view, proj matrices (uniforms uModel, uView, uProj)
    void setMatMVP(const glm::mat4 & model, const glm::mat4 & view, const glm::mat4 & proj){
        glUniformMatrix4fv(uModel, 1, GL_FALSE, value_ptr(model));
        glUniformMatrix4fv(uView, 1, GL_FALSE, value_ptr(view));
        glUniformMatrix4fv(uProj, 1, GL_FALSE, value_ptr(proj));
    }

    /// Set the material
    void setMaterial(const Material & m){
        glUniform3fv(loc("uMaterial.ambient"), 1, glm::value_ptr(m.ambient));
        glUniform3fv(loc("uMaterial.diffuse"), 1, glm::value_ptr(m.diffuse));
        glUniform3fv(loc("uMaterial.specular"), 1, glm::value_ptr(m.specular));
        glUniform1f(loc("uMaterial.shininess"), m.shininess);
    }

private: //==== Methods
    // Read a whole file as a string
    static std::shared_ptr<std::string> parseFile(const std::string & fileName);

private: //==== Fields
    /// The program's OpenGL id
    GLuint prog = 0;
    /// Uniforms
    GLint uModel, uCam, uView, uProj;
};
}

