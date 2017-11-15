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

    Window window(800, 600, "Goblin OpenGL Fun Backgound");
    
    //-------------------------------------------
    // Shaders
    //-------------------------------------------
    
//    ShaderProg prog = ShaderProg::fromMem(vertexShaderSource, fragmentShaderSource);
    ShaderProg prog = ShaderProg::fromFiles("shaders/vert.vert", "shaders/frag.frag");

    //-------------------------------------------
    // Model, VBO, VAO
    //-------------------------------------------

    // Square, with EBO
    GLfloat verticesSq[] = {
         1.0f,  1.0f, 0.0f,   1.0, 1.0,  // UR
         1.0f, -1.0f, 0.0f,   1.0, 0.0,  // LR
        -1.0f, -1.0f, 0.0f,   0.0, 0.0,  // LL
        -1.0f,  1.0f, 0.0f,   0.0, 1.0   // UL
    };
    GLuint indicesSq[] = {
        0, 1, 3,
        1, 2, 3
    };

    // VAO for square (EBO)
    Vao vao({3, 0, 2}, verticesSq, sizeof(verticesSq), indicesSq, sizeof(indicesSq));

    // Textures
    Tex tex = Tex::fromFile("common_textures/elves.jpg");

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

        tex.bind(0);
        glUniform1i(prog.loc("uTex"), 0);

        vao.draw();

        glBindVertexArray(0);
        
        // Draw the window (Swap buffers)
        window.swapBuffers();
    }

    glfwTerminate(); // Stop openGL
    return 0;
}
