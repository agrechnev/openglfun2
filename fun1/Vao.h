#pragma once
// By Oleksiy Grechnyev

// OpenGL Headers
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW (after GLEW)
#include <GLFW/glfw3.h>

#include "./IVao.h"

namespace MotokoGL {
class Vao : public IVao
{
public: // ====== Constructor =====
    Vao();

public: // ====== Method
    /// Draw this VAO object
    virtual void draw() override {

    }

private: // Fields
    /// Are we using EBO ?
    bool useEbo = false;

    /// GL ids of vao, vbo and ebo
    GLuint vao=0, vbo=0, ebo=0;
};
}
