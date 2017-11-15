// By Oleksiy Grechnyev
// FUN1: fun with OpenGL
// Draw a triangle (or, optionally, rectangle) with MotokoGL library


// System headers
#include <iostream>
#include <string>

#include "MotokoGL.h"

//=============================================================
int main(){
    using namespace MotokoGL;

    Window window(800, 600, "Goblin OpenGL Fun 1");
    
    //-------------------------------------------
    // Shaders
    //-------------------------------------------
    
//    ShaderProg prog = ShaderProg::fromMem(vertexShaderSource, fragmentShaderSource);
    ShaderProg prog = ShaderProg::fromFiles("shaders/vert.vert", "shaders/frag.frag");

    //-------------------------------------------
    // Model, VBO, VAO
    //-------------------------------------------
    // One triangle, w/o EBO
    GLfloat verticesTr[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Square, with EBO
    GLfloat verticesSq[] = {
         0.5f,  0.5f, 0.0f, // UR
         0.5f, -0.5f, 0.0f, // LR
        -0.5f, -0.5f, 0.0f, // LL
        -0.5f,  0.5f, 0.0f  // UL
    };
    GLuint indicesSq[] = {
        0, 1, 3,
        1, 2, 3
    };

    // VAO for square (EBO)
//    Vao vao({3}, verticesSq, sizeof(verticesSq), indicesSq, sizeof(indicesSq));

    // VAO for triangle (no EBO)
    Vao vao({3}, verticesTr, sizeof(verticesTr));
    
    //-------------------------------------------
    // GLFW game loop

    while (!window.shouldClose() ){
        glfwPollEvents();
        
        // Render
        
        // Clear screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw our model
        prog.use();
        vao.draw();

        glBindVertexArray(0);
        
        // Draw the window (Swap buffers)
        window.swapBuffers();
    }

    glfwTerminate(); // Stop openGL
    return 0;
}
