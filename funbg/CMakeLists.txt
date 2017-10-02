cmake_minimum_required(VERSION 3.0)
project (funbg)

set (CMAKE_CXX_STANDARD 14)

# Copy directories
file(COPY shaders DESTINATION .)
file(COPY ../common_textures DESTINATION .)

# Source files
set (SOURCE_FILES
        funbg.cpp
      )
      
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} MotokoGL Soil ${GL_LIBS})
