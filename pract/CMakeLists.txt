cmake_minimum_required(VERSION 3.0)
project (openglfun2_pract)

set (CMAKE_CXX_STANDARD 14)

# Find GLFW, GLEW
FIND_LIBRARY(GLFW_LIB NAMES glfw glfw3 glfw.3.2)
message("GLFW_LIB = ${GLFW_LIB}")
if(NOT ${APPLE})
    FIND_LIBRARY(GLEW_LIB NAMES glew GLEW glew32)
endif()
message("GLEW_LIB = ${GLEW_LIB}")

# Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(OPENGL_INCLUDE_DIR)
message("OPENGL_gl_LIBRARY = ${OPENGL_gl_LIBRARY}")
message("OPENGLu_gl_LIBRARY = ${OPENGL_glu_LIBRARY}")
message("OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")
message("OPENGL_INCLUDE_DIR = ${OPENGL_INCLUDE_DIR}")

# All GL libs
set(GL_LIBS  ${GLEW_LIB} ${GLFW_LIB} ${OPENGL_LIBRARIES})
message("GL_LIBS = ${GL_LIBS}")

# Build MotokoGL library
add_subdirectory(MotokoGL)
include_directories(MotokoGL )

# Build all targets
add_subdirectory(p1)
add_subdirectory(home1)
add_subdirectory(triangle)
