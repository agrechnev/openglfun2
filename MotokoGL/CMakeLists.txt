cmake_minimum_required(VERSION 3.0)
project (MotokoGL)

set (CMAKE_CXX_STANDARD 14)

# Source files
set (SOURCE_FILES
      ./glheader.h
      ./fatal.h
      ./Window.cpp ./Window.h
      ./ShaderProg.cpp ./ShaderProg.h
      ./IVao.h
      ./Vao.h ./Vao.cpp
      ./texture.h ./texture.cpp
      ./MotokoGL.h
      )

add_library(MotokoGL ${SOURCE_FILES})
