# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\prog\JetBrains\CLion 2016.3.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\prog\JetBrains\CLion 2016.3.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\alex\clion\openglfun2\pract

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\alex\clion\openglfun2\pract\cmake-build-debug

# Include any dependencies generated for this target.
include p1/CMakeFiles/p1.dir/depend.make

# Include the progress variables for this target.
include p1/CMakeFiles/p1.dir/progress.make

# Include the compile flags for this target's objects.
include p1/CMakeFiles/p1.dir/flags.make

p1/CMakeFiles/p1.dir/main.cpp.obj: p1/CMakeFiles/p1.dir/flags.make
p1/CMakeFiles/p1.dir/main.cpp.obj: p1/CMakeFiles/p1.dir/includes_CXX.rsp
p1/CMakeFiles/p1.dir/main.cpp.obj: ../p1/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\alex\clion\openglfun2\pract\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object p1/CMakeFiles/p1.dir/main.cpp.obj"
	cd /d D:\alex\clion\openglfun2\pract\cmake-build-debug\p1 && D:\msys32\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\p1.dir\main.cpp.obj -c D:\alex\clion\openglfun2\pract\p1\main.cpp

p1/CMakeFiles/p1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p1.dir/main.cpp.i"
	cd /d D:\alex\clion\openglfun2\pract\cmake-build-debug\p1 && D:\msys32\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\alex\clion\openglfun2\pract\p1\main.cpp > CMakeFiles\p1.dir\main.cpp.i

p1/CMakeFiles/p1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p1.dir/main.cpp.s"
	cd /d D:\alex\clion\openglfun2\pract\cmake-build-debug\p1 && D:\msys32\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\alex\clion\openglfun2\pract\p1\main.cpp -o CMakeFiles\p1.dir\main.cpp.s

p1/CMakeFiles/p1.dir/main.cpp.obj.requires:

.PHONY : p1/CMakeFiles/p1.dir/main.cpp.obj.requires

p1/CMakeFiles/p1.dir/main.cpp.obj.provides: p1/CMakeFiles/p1.dir/main.cpp.obj.requires
	$(MAKE) -f p1\CMakeFiles\p1.dir\build.make p1/CMakeFiles/p1.dir/main.cpp.obj.provides.build
.PHONY : p1/CMakeFiles/p1.dir/main.cpp.obj.provides

p1/CMakeFiles/p1.dir/main.cpp.obj.provides.build: p1/CMakeFiles/p1.dir/main.cpp.obj


# Object files for target p1
p1_OBJECTS = \
"CMakeFiles/p1.dir/main.cpp.obj"

# External object files for target p1
p1_EXTERNAL_OBJECTS =

p1/p1.exe: p1/CMakeFiles/p1.dir/main.cpp.obj
p1/p1.exe: p1/CMakeFiles/p1.dir/build.make
p1/p1.exe: MotokoGL/libMotokoGL.a
p1/p1.exe: D:/msys32/mingw32/lib/libglew32.dll.a
p1/p1.exe: D:/msys32/mingw32/lib/libglfw3.dll.a
p1/p1.exe: p1/CMakeFiles/p1.dir/linklibs.rsp
p1/p1.exe: p1/CMakeFiles/p1.dir/objects1.rsp
p1/p1.exe: p1/CMakeFiles/p1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\alex\clion\openglfun2\pract\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable p1.exe"
	cd /d D:\alex\clion\openglfun2\pract\cmake-build-debug\p1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\p1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
p1/CMakeFiles/p1.dir/build: p1/p1.exe

.PHONY : p1/CMakeFiles/p1.dir/build

p1/CMakeFiles/p1.dir/requires: p1/CMakeFiles/p1.dir/main.cpp.obj.requires

.PHONY : p1/CMakeFiles/p1.dir/requires

p1/CMakeFiles/p1.dir/clean:
	cd /d D:\alex\clion\openglfun2\pract\cmake-build-debug\p1 && $(CMAKE_COMMAND) -P CMakeFiles\p1.dir\cmake_clean.cmake
.PHONY : p1/CMakeFiles/p1.dir/clean

p1/CMakeFiles/p1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\alex\clion\openglfun2\pract D:\alex\clion\openglfun2\pract\p1 D:\alex\clion\openglfun2\pract\cmake-build-debug D:\alex\clion\openglfun2\pract\cmake-build-debug\p1 D:\alex\clion\openglfun2\pract\cmake-build-debug\p1\CMakeFiles\p1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : p1/CMakeFiles/p1.dir/depend
