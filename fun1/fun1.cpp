// By Oleksiy Grechnyev
// FUN1: fun with OpenGL

#include "./glheader.h"

// System headers
#include <iostream>
#include <string>

// Local headers
#include "./fatal.h"
#include "./Window.h"
#include "./ShaderProg.h"
#include "./Vao.h"

//=============================================================
int main(){
    using namespace MotokoGL;

    Window window(800, 600, "Goblin OpenGL Fun 1");
    
    //-------------------------------------------
    // Shaders
    //-------------------------------------------
    // Source
    const GLchar * vertexShaderSource =
        "#version 330 core\n"
        "layout (location=0) in vec3 pos;\n"
        "void main(){\n"
        "gl_Position=vec4(pos.x, pos.y, pos.z, 1.0);}\n\0"; 
    
    const GLchar * fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main(){\n"
        "color=vec4(1.0f, 0.9f, 0.0f, 1.0f);}\n\0";
    
    ShaderProg prog = ShaderProg::fromMem(vertexShaderSource, fragmentShaderSource);
    
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

    // VAO for square
    Vao vao({3}, verticesSq, sizeof(verticesSq), indicesSq, sizeof(indicesSq));

    // Attrib pointer
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    
    //-------------------------------------------
    // GLFW game loop

    while (!window.shouldClose() ){
        glfwPollEvents();
        
        // Render
        
        // Clear screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw our model here
        prog.use();
        vao.draw();

        glBindVertexArray(0);
        
        // Draw the window (Swap buffers)
        window.swapBuffers();
    }

    glfwTerminate(); // Stop openGL
    return 0;
}
