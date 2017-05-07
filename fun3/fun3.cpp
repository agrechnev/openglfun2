// By Oleksiy Grechnyev
// FUN3: FUN with OpenGL: Basic Lighting

// System headers
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

// MotokoGL
#include "MotokoGL.h"

//=============================================================
// Globals (if any)


//=============================================================
inline static GLfloat funCos(GLfloat x){
    return 0.5f*(cosf(x) + 1);
}
//=============================================================

//float random number between 0.0f and 1.0f
inline static float randf(){
    return (float)rand()/(float)RAND_MAX;
}
//=============================================================

// Random unit 3-vector with spherical distribution
static glm::vec3 randUV3(){
    float t = acos(2*randf()-1);
    float p = M_PI*2*randf();
    glm::vec3 result(sin(t)*cos(p), sin(t)*sin(p), cos(t));
    return result;
}
//=============================================================
int main(){
    using namespace MotokoGL;
    using namespace glm;
    using namespace std;

    // Seed random number generator
    srand(time(NULL));

    // Create window
    Window window(1000, 800, "Goblin OpenGL Fun 2");
    const float aspectRatio = 1.0f*window.getWidth()/window.getHeight();

    glEnable(GL_DEPTH_TEST); // Enable depth test, important
    
    //-------------------------------------------
    // Programs and Shaders
    //-------------------------------------------
    
    //    ShaderProg prog = ShaderProg::fromMem(vertexShaderSource, fragmentShaderSource);
    ShaderProg objProg = ShaderProg::fromFiles("shaders/vert.vert", "shaders/obj.frag");
    ShaderProg lampProg = ShaderProg::fromFiles("shaders/vert.vert", "shaders/lamp.frag");

    //-------------------------------------------
    // Model, VBO, VAO
    //-------------------------------------------

    // A cube XYZ_NORMAL
    GLfloat vert[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // VAO
    // Note: we don't use textures at the moment, but can easily put them back
    Vao objVao({3, 3}, vert, sizeof(vert));
    Vao lampVao({3, 3}, vert, sizeof(vert));

    //-------------------------------------------
    // Textures

    //    Tex tex1 = Tex::fromFile("common_textures/container.jpg");
    //    Tex tex2 = Tex::fromFile("common_textures/awesomeface.png");


    //-------------------------------------------
    // Camera
    SimpleCamera camera;
    camera.aspect = aspectRatio;

    //-------------------------------------------
    // Lamp position
    vec3 lampPos(1.2f, 1.0f, 2.0f);

    //-------------------------------------------
    //-------------------------------------------
    // GLFW game loop
    //-------------------------------------------
    while (!window.shouldClose() ){
        glfwPollEvents(); // Events
        GLfloat t = glfwGetTime(); // Time in seconds

        // Now Render everything
        
        // Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Prepare to draw the model


        // Set up textures
        //        tex1.bind(0);
        //        glUniform1i(prog.loc("uTex1"), 0);
        //        tex2.bind(1);
        //        glUniform1i(prog.loc("uTex2"), 1);

        // Set up the camera pos if needed
        camera.pos = vec3(0.0f, 0.0f, 10.0f);

        // Camera matrix
        mat4 cam = camera.matrix();

        // Model matrix
        mat4 model;

        //===== Draw the lamp
        lampProg.use(); // Use program
        model = mat4();
        model = translate(model, lampPos); // To position
        model = scale(model, vec3(0.2f)); // Smaller

        lampProg.setMat(cam, model);
        lampVao.draw();

        //===== Draw the cube
        objProg.use(); // Use program

        // Set colors
        glUniform3f(objProg.loc("uObjectC"), 1.0f, 0.5f, 0.31f);
        glUniform3f(objProg.loc("uLightC"), 1.0f, 1.0f, 1.0f);

        //            model = translate(model, cubePositions[i]);
        model = mat4();
        model = rotate(model, t*0.7f, vec3(1.0f, 0.5f, 0.0f)); // Rotate

        objProg.setMat(cam, model);
        objVao.draw(); // Draw

        // Draw the window (Swap buffers)
        window.swapBuffers();
    }

    glfwTerminate(); // Stop openGL
    return 0;
}
