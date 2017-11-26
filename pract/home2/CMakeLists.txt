cmake_minimum_required(VERSION 3.0)
project (home2)
set (CMAKE_CXX_STANDARD 14)

# Copy directories
file(COPY shaders DESTINATION .)
file(COPY ../common_textures DESTINATION .)
file(COPY tex DESTINATION .)

# Source files
set (SOURCE_FILES
      ./main.cpp
      ./vaofactory.h ./vaofactory.cpp
      )
      
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} MotokoGL ${GL_LIBS})
