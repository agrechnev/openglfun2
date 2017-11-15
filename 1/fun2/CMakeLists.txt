cmake_minimum_required(VERSION 3.0)
project (fun2)

set (CMAKE_CXX_STANDARD 14)

# Copy directories
file(COPY shaders DESTINATION .)
file(COPY ../common_textures DESTINATION .)

# Source files
set (SOURCE_FILES
      ./fun2.cpp
      )

add_executable(fun2 ${SOURCE_FILES})
target_link_libraries(fun2 MotokoGL Soil ${GL_LIBS})
