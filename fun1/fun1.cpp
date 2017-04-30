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
        "color=vec4(1.0f, 0.0f, 0.0f, 1.0f);}\n\0";
    
    ShaderProg prog = ShaderProg::fromMem(vertexShaderSource, fragmentShaderSource);
    
    //-------------------------------------------
    // Model, VBO, VAO
    //-------------------------------------------
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    // VBO, VAO
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Bind VAO first
    glBindVertexArray(VAO);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    // VBO to VAO
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
        
        // Draw the triangle here
        prog.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // Draw the window (Swap buffers)
        window.swapBuffers();
    }
    
    glfwTerminate(); // Stop openGL
    return 0;
}
