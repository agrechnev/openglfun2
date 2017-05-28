// By Oleksiy Grechnyev
// FUN5: FUN with OpenGL: Basic Lighting: Material maps

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
    Window window(1000, 800, "Goblin OpenGL Fun 5");
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

    // A cube XYZ_NORMAL_TEX

    GLfloat vert[] = {
        // Positions          // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };


    // VAO
    // XYZ_NORM_TEX
    Vao objVao({3, 3, 2}, vert, sizeof(vert));
    Vao lampVao({3, 3, 2}, vert, sizeof(vert));

    //-------------------------------------------
    // Material + textures

    Tex texAD = Tex::fromFile("common_textures/container2.png");
    MaterialT materialT(
        texAD,
        texAD,
        Tex::fromFile("common_textures/container2_specular.png"),
        Tex::fromFile("common_textures/matrix.jpg"),
        32.0f,
        //MaterialT::F_AMBIENT |  MaterialT::F_DIFFUSE | MaterialT::F_SPECULAR |  MaterialT::F_EMISSION
        MaterialT::F_AMBIENT |  MaterialT::F_DIFFUSE | MaterialT::F_SPECULAR
    );

    //-------------------------------------------
    // Light
    Light light(
    {1.2f, 1.0f, 2.0f},
    {0.2f, 0.2f, 0.2f},
    {0.5f, 0.5f, 0.5f},
    {1.0f, 1.0f, 1.0f}
                );
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
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Prepare to draw the model

        // Set up the camera pos if needed
        camera.pos = vec3(2.0f, 2.0f, 7.0f);

        // Camera matrix
        mat4 cam = camera.matrix();

        // Model matrix
        mat4 model;

        // Let's make some funny light color
        vec3 lightColor(funCos(t*2), funCos(t*0.7), funCos(t*1.3));
        light.ambient = lightColor * 0.2f;
        light.diffuse = lightColor * 0.5f;
        light.specular = lightColor;

        //===== Draw the lamp
        lampProg.use(); // Use program

        // Set model, cam
        model = mat4();
        model = translate(model, light.position); // To position
        model = scale(model, vec3(0.1f)); // Smaller
        lampProg.setMatCM(cam, model);

        lampProg.setLight(light); // Set the light

        lampVao.draw(); // Draw lamp

        //===== Draw the cube
        objProg.use(); // Use program

        // Set camera pos
        glUniform3fv(objProg.loc("uCamPos"), 1, value_ptr(camera.pos));

        //            model = translate(model, cubePositions[i]);

        // Set model matrix
        model = mat4();
        model = rotate(model, t*sqrtf(0.5f), vec3(1.0f, 0.5f, 0.0f)); // Rotate

        objProg.setMatCM(cam, model);
        objProg.setMatN(model);

        // Set material
        objProg.setMaterialT(materialT);

        // Set light
        objProg.setLight(light);

        objVao.draw(); // Draw cube

        // Draw the window (Swap buffers)
        window.swapBuffers();
    }

    glfwTerminate(); // Stop openGL
    return 0;
}
