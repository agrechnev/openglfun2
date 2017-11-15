// By Oleksiy Grechnyev
// A simplest possible opengl program, paint a triangle

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW (after GLEW)
#include <GLFW/glfw3.h>

// System headers
#include <iostream>
#include <string>

//=============================================================
static void fatal(const string & msg){
    std::cerr << msg << std::endl;
    glfwTerminate();
    exit(-1);
}
//=============================================================
static void fatal2(const string & msg1, const string & msg2){
    std::cerr << msg1 << " : " << std::endl;
    glfwTerminate();
    exit(-1);
}
//=============================================================
// Error callback for GLFW
static void errorCB(int i, const char * msg){
    std::cerr << " errorCB : " << i << ":" << msg << std::endl;
}
//=============================================================
int main(){
    // Init GLFW
    glfwInit();
    
    glfwSetErrorCallback(errorCB);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Do we need it ?
    
    // Create GLFW window
    GLFWwindow * window = glfwCreateWindow(800, 600, "OpenGL Triangle", nullptr, nullptr);
    if (window == nullptr)
        fatal("Cannot create GLFW window !");
  
    glfwMakeContextCurrent(window); // Doesn't work without it ;)
  
    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        fatal("Cannot initialize GLEW !");
    
    // From now on
    // Set viewport (should be equal to the window size)
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    // The first OpenGL function call
    glViewport(0, 0, width, height);
    
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
    
    // Create shaders and Compile
    // Vertex
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        fatal2("Cannot compile vertex shader", infoLog);
    } 
    
    // Fragment
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        fatal2("Cannot compile fragment shader", infoLog);
    }
    
    // Shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        fatal2("Cannot link shader program", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
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
    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        
        // Render
        
        // Clear screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw the triangle here
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // Draw the window (note : here's GLFW, not GL !)
        glfwSwapBuffers(window);
    }

    // Delete VAO, VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    return 0;
}
