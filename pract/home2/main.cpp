// By Oleksiy Grechnyev 2017
// OpenGL homework 1 : draw a clipart human figure

#include <cmath>
#include <thread>

#include "MotokoGL.h"

#include "./vaofactory.h"

int main(){
    using namespace std;
    using namespace MotokoGL;
    Window window(1000, 750, "Goblin OpenGL Homework 2", 4, 5);  // The Window

    // Promrams
    // No texture Prog
    ShaderProg progNT = ShaderProg::fromFiles("shaders/vert_notex.glsl", "shaders/frag_notex.glsl");
    // Texture Prog
    ShaderProg progT = ShaderProg::fromFiles("shaders/vert_tex.glsl", "shaders/frag_tex.glsl");
    // Textures
    Tex texCM = Tex::fromFile("tex/chainmail.jpg");
    Tex texM = Tex::fromFile("tex/metal.jpg");
    Tex texS = Tex::fromFile("tex/shield.png");
    Tex texI = Tex::fromFile("tex/inferno.jpg");
    //-------------------------------------------
    // VAOs for different parts
    Vao vBackground({3, 0, 2}, {
                        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // UL
                        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // LL
                        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // LR
                        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // UR
                    },  { 0 , 1, 2, 2, 3, 0});

    Vao vHead = createRPoly(0, 0.5, 0.15*3/4, 0.15, 50);
    Vao vTorso({3, 0, 2}, {
                   -0.3f,  0.3f, 0.0f,  0.0f, 0.7f,  // UL
                   -0.15f, -0.4f, 0.0f, 0.15f, 0.0f,  // LL
                   0.15f, -0.4f, 0.0f,  0.45f, 0.0f,   // LR
                   0.3f,  0.3f, 0.0f,   0.6f, 0.7f  // UR
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

    Vao vSword({3, 0, 2}, {
                   -0.7f,  0.9f, 0.0f, 0.1f, 0.9f,
                   -0.77f,  0.75f, 0.0f, 0.03f, 0.75f,
                   -0.7f,  0.0f, 0.0f, 0.1f, 0.0f,
                   -0.63f,  0.75f, 0.0f, 0.17f, 0.75f
               } , { 0 , 1, 2, 2, 3, 0});

    Vao vGuard({3, 0, 2}, {
                   -0.8f,  0.2f, 0.0f, 0.0f, 0.2f,
                   -0.8f,  0.15f, 0.0f, 0.0f, 0.15f,
                   -0.6f,  0.15f, 0.0f, 0.2f, 0.15f,
                   -0.6f,  0.2f, 0.0f, 0.2f, 0.2f
               } , { 0 , 1, 2, 2, 3, 0});

    Vao vShield = createRPolyTex(0.4, -0.1, 0.3*3/4, 0.3, 50);
    //-------------------------------------------
    // GLFW game loop
    GLint uColor = progNT.loc("uColor"); // A uniform
    while (!window.shouldClose() ){
        glfwPollEvents();

        // Clear screen
        //        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw background
        progT.use();  // Tex prog
        texI.bind(0);
        glUniform1i(progT.loc("uTex1"), 0);
        vBackground.draw();

        // Draw the model
        progNT.use();  // Notex prog
        glUniform4f(uColor, 1.0f, 1.0f, 0.0f, 1.0f); // Yellow
        vHead.draw();
        vLegs.draw();
        vArms.draw();

        progT.use();  // Tex prog
        texCM.bind(0);
        glUniform1i(progT.loc("uTex1"), 0);
        vTorso.draw();
        texM.bind(0);
        vSword.draw();
        vGuard.draw();
        texS.bind(0);
        vShield.draw();



        window.swapBuffers(); // The actual draw
        this_thread::sleep_for(chrono::milliseconds(15));
    }
    return 0;
}
