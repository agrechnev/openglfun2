cmake_minimum_required(VERSION 3.0)
project (openglfun2)

set (CMAKE_CXX_STANDARD 14)

# Fun with FIND_LIBRARY
FIND_LIBRARY(GLFW_LIB NAMES glfw glfw3)
FIND_LIBRARY(GLEW_LIB NAMES glew GLEW glew32)

find_package(OpenGL REQUIRED)
message("OPENGL_gl_LIBRARY = ${OPENGL_gl_LIBRARY}")
message("OPENGLu_gl_LIBRARY = ${OPENGL_glu_LIBRARY}")

set(GL_LIBS  ${GLEW_LIB} ${GLFW_LIB} ${OPENGL_gl_LIBRARY})

message("GL_LIBS = ${GL_LIBS}")

# Set include dirs
include_directories(
    MotokoGL 
    Soil
)

# Build SOIL library
add_subdirectory(Soil)

# Build MotokoGL library
add_subdirectory(MotokoGL)

# Build all examples
add_subdirectory(triangle)
add_subdirectory(fun1)
add_subdirectory(fun2)
add_subdirectory(fun3)
add_subdirectory(fun3v)
add_subdirectory(fun3p)
add_subdirectory(fun4)
add_subdirectory(fun5)
add_subdirectory(funbg)
