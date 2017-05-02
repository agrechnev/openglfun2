// By Oleksiy Grechnyev
// FUN2: More FUN with OpenGL


// System headers
#include <iostream>
#include <string>
#include <cmath>

#include "MotokoGL.h"

//=============================================================
inline static GLfloat funCos(GLfloat x){
    return 0.5f*(cos(x) + 1);
}
//=============================================================
int main(){
    using namespace MotokoGL;

    Window window(800, 600, "Goblin OpenGL Fun 2");
    
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


    // Some funny vertices

    // XYZ_RGB_ST
    GLfloat vert[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.00f, 1.00f,   // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.00f, 0.00f,   // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.00f, 0.00f,   // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.00f, 1.00f    // Top Left
    };

    // VAO
    Vao vao({3, 3, 2}, vert, sizeof(vert), indicesSq, sizeof(indicesSq));


    // VAO for square (EBO)
    //    Vao vao({3}, verticesSq, sizeof(verticesSq), indicesSq, sizeof(indicesSq));

    // VAO for triangle (no EBO)
    //    Vao vao({3}, verticesTr, sizeof(verticesTr));
    
    // If you want wireframe
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //-------------------------------------------
    // Texture

    Tex tex1 = Tex::fromFile("common_textures/container.jpg");
    Tex tex2 = Tex::fromFile("common_textures/awesomeface.png");

    //-------------------------------------------
    // GLFW game loop

    // Uniform locations, if any

    while (!window.shouldClose() ){
        glfwPollEvents(); // Events
        GLfloat t = glfwGetTime(); // Time in seconds

        // Now Render everything
        
        // Clear screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT);

        // Set up textures
        tex1.bind(0);
        glUniform1i(prog.loc("uTex1"), 0);
        tex2.bind(1);
        glUniform1i(prog.loc("uTex2"), 1);

        glUniform1f(prog.loc("uMix"), funCos(t));

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
