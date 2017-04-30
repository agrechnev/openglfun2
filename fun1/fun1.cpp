// By Oleksiy Grechnyev
// FUN1: fun with OpenGL

// OpenGL Headers
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW (after GLEW)
#include <GLFW/glfw3.h>

// System headers
#include <iostream>
#include <string>

// Local headers
#include "./fatal.h"
#include "./Window.h"
#include "./ShaderProg.h"

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

    // VBO, VAO, EBO
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind VAO first
    glBindVertexArray(VAO);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSq), verticesSq, GL_STATIC_DRAW);

    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSq), indicesSq, GL_STATIC_DRAW);

    // Attrib pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    // Unbind VBO, then VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // Unbind VAO
    
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
        glBindVertexArray(VAO);

        // Draw w/o ebo
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Draw with ebo
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        
        // Draw the window (Swap buffers)
        window.swapBuffers();
    }

    // Delete VAO, VBO, EBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate(); // Stop openGL
    return 0;
}
