cmake_minimum_required(VERSION 3.0)
project (fun4)

set (CMAKE_CXX_STANDARD 14)

# Copy directories
file(COPY shaders DESTINATION .)
file(COPY ../common_textures DESTINATION .)

# Source files
set (SOURCE_FILES
      ./fun4.cpp
      )

add_executable(fun4 ${SOURCE_FILES})
target_link_libraries(fun4 MotokoGL Soil ${GL_LIBS})
