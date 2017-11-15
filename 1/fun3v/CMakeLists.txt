cmake_minimum_required(VERSION 3.0)
project (fun3v)

set (CMAKE_CXX_STANDARD 14)

# Copy directories
file(COPY shaders DESTINATION .)
file(COPY ../common_textures DESTINATION .)

# Source files
set (SOURCE_FILES
      ./fun3v.cpp
      )

add_executable(fun3v ${SOURCE_FILES})
target_link_libraries(fun3v MotokoGL Soil ${GL_LIBS})
