cmake_minimum_required(VERSION 3.0)
project (fun1)

set (CMAKE_CXX_STANDARD 14)

# Fun with FIND_LIBRARY
FIND_LIBRARY(GLFW_LIB NAMES glfw glfw3)
FIND_LIBRARY(GLEW_LIB NAMES glew GLEW glew32)
FIND_LIBRARY(GL_LIB NAMES gl GL opengl opengl32)

# Source files
set (SOURCE_FILES
      ./fatal.h
      ./fun1.cpp
      ./Window.cpp ./Window.h
      ./ShaderProg.cpp ./ShaderProg.h
      ./IVao.h
      )
      
      
# MESSAGE( STATUS "GLFW_LIB = " ${GLFW_LIB})

add_executable(fun1 ${SOURCE_FILES})
target_link_libraries(fun1 ${GLFW_LIB} ${GLEW_LIB} ${GL_LIB})
