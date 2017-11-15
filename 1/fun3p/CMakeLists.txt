cmake_minimum_required(VERSION 3.0)
project (fun3p)

set (CMAKE_CXX_STANDARD 14)

# Copy directories
file(COPY shaders DESTINATION .)
file(COPY ../common_textures DESTINATION .)

# Source files
set (SOURCE_FILES
      ./fun3p.cpp
      )

add_executable(fun3p ${SOURCE_FILES})
target_link_libraries(fun3p MotokoGL Soil ${GL_LIBS})
