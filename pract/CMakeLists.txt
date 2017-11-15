cmake_minimum_required(VERSION 3.0)
project (openglfun2_pract)

set (CMAKE_CXX_STANDARD 14)

# Fun with FIND_LIBRARY
FIND_LIBRARY(GLFW_LIB NAMES glfw glfw3)
FIND_LIBRARY(GLEW_LIB NAMES glew GLEW glew32)

find_package(OpenGL REQUIRED)
message("OPENGL_gl_LIBRARY = ${OPENGL_gl_LIBRARY}")
message("OPENGLu_gl_LIBRARY = ${OPENGL_glu_LIBRARY}")

set(GL_LIBS  ${GLEW_LIB} ${GLFW_LIB} ${OPENGL_gl_LIBRARY})

message("GL_LIBS = ${GL_LIBS}")

include_directories(MotokoGL )


# Build MotokoGL library
add_subdirectory(MotokoGL)

# Build all subdirs
add_subdirectory(p1)
add_subdirectory(triangle)
