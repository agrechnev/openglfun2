#include <iostream>

#include "MotokoGL.h"

using namespace std;

int main(){
    using namespace MotokoGL;
    Window window(800, 600, "Goblin OpenGL Practice 1");  // Window
    // Shaders
    ShaderProg prog = ShaderProg::fromFiles("shaders/vert.glsl", "shaders/frag.glsl");
    // Square with EBO
    GLfloat verticesSq[] = {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // UR
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // LR
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // LL
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // UL
    };
    GLuint indicesSq[] = {
            0, 1, 3,
            1, 2, 3
    };
    // VAO for square with EBO
    Vao vao({3, 0, 2}, verticesSq, sizeof(verticesSq), indicesSq, sizeof(indicesSq));
    cout << "count = " << vao.getCount() << endl;
    Tex tex1 = Tex::fromFile("common_textures/elves.jpg");  // Texture
    //-------------------------------------------
    // GLFW game loop
    while (!window.shouldClose() ){
        glfwPollEvents();

        // Render
        // Clear screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw the model
        prog.use();
        tex1.bind(0);
        glUniform1i(prog.loc("uTex1"), 0);
        vao.draw();

        window.swapBuffers(); // The actual draw
    }
    return 0;
}
