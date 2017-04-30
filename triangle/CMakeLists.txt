cmake_minimum_required(VERSION 3.0)
project (triangle)

set (CMAKE_CXX_STANDARD 14)

# Fun with FIND_LIBRARY
FIND_LIBRARY(GLFW_LIB NAMES glfw glfw3)
FIND_LIBRARY(GLEW_LIB NAMES glew GLEW glew32)
FIND_LIBRARY(GL_LIB NAMES gl GL opengl opengl32)

# Source files
set (SOURCE_FILES
      ./triangle.cpp
      )
      
      
# MESSAGE( STATUS "GLFW_LIB = " ${GLFW_LIB})

add_executable(triangle ${SOURCE_FILES})
#target_link_libraries(triangle glfw3 glew32 opengl32)
target_link_libraries(triangle ${GLFW_LIB} ${GLEW_LIB} ${GL_LIB})