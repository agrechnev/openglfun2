cmake_minimum_required(VERSION 3.0)
project (fun1)

set (CMAKE_CXX_STANDARD 14)

# Copy directories
file(COPY shaders DESTINATION .)


# Source files
set (SOURCE_FILES
      ./fun1.cpp
      )
      
# MESSAGE( STATUS "GLFW_LIB = " ${GLFW_LIB})

add_executable(fun1 ${SOURCE_FILES})
target_link_libraries(fun1 MotokoGL ${GL_LIBS})
