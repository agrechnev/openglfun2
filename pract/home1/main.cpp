// By Oleksiy Grechnyev 2017
// OpenGL homework 1 : draw a clipart human figure

#include <cmath>
#include <thread>

#include "MotokoGL.h"

#include "./vaofactory.h"

int main(){
    using namespace std;
    using namespace MotokoGL;
    Window window(1000, 750, "Goblin OpenGL Homework 1");  // The Window
    // Shaders
    ShaderProg prog = ShaderProg::fromFiles("shaders/vert.glsl", "shaders/frag.glsl");
    //-------------------------------------------
    // VAOs for different parts
    Vao vHead = createRPoly(0, 0.5, 0.15*3/4, 0.15, 50);
    Vao vTorso({3}, {
                    -0.3f,  0.3f, 0.0f,  // UL
                    -0.15f, -0.4f, 0.0f,  // LL
                    0.15f, -0.4f, 0.0f,   // LR
                    0.3f,  0.3f, 0.0f  // UR
                } , { 0 , 1, 2, 2, 3, 0});

    Vao vLegs({3}, {
                  -0.15f, -0.41f, 0.0f,
                  -0.15f, -0.95f, 0.0f,
                  -0.09f, -0.95f, 0.0f,
                  -0.09f, -0.41f, 0.0f,
                  0.09f, -0.41f, 0.0f,
                  0.09f, -0.95f, 0.0f,
                  0.15f, -0.95f, 0.0f,
                  0.15f, -0.41f, 0.0f
              }, { 0 , 1, 2, 2, 3, 0,  4, 5, 6 , 6 ,7, 4});

    Vao vArms({3}, {
                  -0.3f, 0.3f, 0.0f,
                  -0.7f, 0.1f, 0.0f,
                  -0.7f, 0.0f, 0.0f,
                  -0.28f, 0.2f, 0.0f,
                  0.3f, 0.3f, 0.0f,
                  0.28f, 0.2f, 0.0f,
                  0.3f, 0.17f, 0.0f,
                  0.4f, 0.17f, 0.0f
              }, { 0 , 1, 2, 2, 3, 0,  4, 5, 6 , 6 ,7, 4});

    Vao vSword({3}, {
                    -0.7f,  0.9f, 0.0f,
                    -0.77f,  0.75f, 0.0f,
                    -0.7f,  0.0f, 0.0f,
                   -0.63f,  0.75f, 0.0f
                } , { 0 , 1, 2, 2, 3, 0});

    Vao vGuard({3}, {
                   -0.8f,  0.2f, 0.0f,
                   -0.8f,  0.15f, 0.0f,
                   -0.6f,  0.15f, 0.0f,
                   -0.6f,  0.2f, 0.0f
               } , { 0 , 1, 2, 2, 3, 0});

    Vao vShield = createRPoly(0.4, -0.1, 0.3*3/4, 0.3, 50);
    //-------------------------------------------
    // GLFW game loop
    GLint uColor = prog.loc("uColor"); // A uniform
    while (!window.shouldClose() ){
        glfwPollEvents();

        // Clear screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the model
        prog.use();

        glUniform4f(uColor, 1.0f, 1.0f, 0.0f, 1.0f); // Yellow
        vHead.draw();
        vLegs.draw();
        vArms.draw();
        glUniform4f(uColor, 0.0f, 1.0f, 0.0f, 1.0f); // Green
        vTorso.draw();
        glUniform4f(uColor, 1.0f, 0.0f, 0.0f, 1.0f); // Red
        vShield.draw();
        vSword.draw();
        vGuard.draw();

        window.swapBuffers(); // The actual draw
        this_thread::sleep_for(chrono::milliseconds(15));
    }
    return 0;
}
