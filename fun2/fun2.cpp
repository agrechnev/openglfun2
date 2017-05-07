// By Oleksiy Grechnyev
// FUN2: More FUN with OpenGL: Camera, textures, rotating cubes


// System headers
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

// MotokoGL
#include "MotokoGL.h"

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
    // Shaders
    //-------------------------------------------
    
    //    ShaderProg prog = ShaderProg::fromMem(vertexShaderSource, fragmentShaderSource);
    ShaderProg prog = ShaderProg::fromFiles("shaders/vert.vert", "shaders/frag.frag");

    //-------------------------------------------
    // Model, VBO, VAO
    //-------------------------------------------

    // A cube XYZ_ST
    GLfloat vert[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // VAO
    Vao vao({3, 0, 2}, vert, sizeof(vert));


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
    // Cube positions
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Random rotation axes and velocities
    vec3 cubeAxes[10];
    float cubeAV[10]; // Angular velocities
    float cubeMV[10]; // Mix velocities
    // Loop over 10 cubes
    for (int cube=0; cube<10; cube++) {
        cubeAV[cube] = 4.0f*randf()-2.0f; // Between -2 and 2 RADIAN / time unit
        cubeMV[cube] = 3.0f*randf()+1.0f;
        cubeAxes[cube] = randUV3(); // Random unit vector
    }

    //-------------------------------------------
    // Camera
    SimpleCamera camera;
    camera.aspect = aspectRatio;


    //-------------------------------------------
    //-------------------------------------------
    // GLFW game loop
    //-------------------------------------------
    while (!window.shouldClose() ){
        glfwPollEvents(); // Events
        GLfloat t = glfwGetTime(); // Time in seconds

        // Now Render everything
        
        // Clear screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Prepare to draw the model

        // Use program
        prog.use();

        // Set up textures
        tex1.bind(0);
        glUniform1i(prog.loc("uTex1"), 0);
        tex2.bind(1);
        glUniform1i(prog.loc("uTex2"), 1);

        // Set up the camera pos
        GLfloat radius = 10.0;
        camera.pos[0] = radius*sinf(t);
        camera.pos[2] = radius*cosf(t);

        // Camera matrix
        mat4 cam = camera.matrix();

        // Draw 10 cubes
        for (int i=0; i<10; i++){

            // Texture mix: fun
            glUniform1f(prog.loc("uMix"), funCos(t*cubeMV[i]));

            // Model matrix
            mat4 model;
            model = translate(model, cubePositions[i]);
            model = rotate(model, t*cubeAV[i], cubeAxes[i]); // Rotate

            prog.setMat(cam, model); // Set matrices
            vao.draw(); // Draw
        }

        // Draw the window (Swap buffers)
        window.swapBuffers();
    }

    glfwTerminate(); // Stop openGL
    return 0;
}
