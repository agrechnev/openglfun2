cmake_minimum_required(VERSION 3.0)
project (triangle)
set (CMAKE_CXX_STANDARD 14)

# Copy directories
#file(COPY shaders DESTINATION .)

# Source files
set (SOURCE_FILES
      ./triangle.cpp
      )
      
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${GL_LIBS})
