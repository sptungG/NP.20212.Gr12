# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /usr/src/cppweb/crow_demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/src/cppweb/crow_demo/build

# Include any dependencies generated for this target.
include CMakeFiles/crow_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/crow_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crow_demo.dir/flags.make

CMakeFiles/crow_demo.dir/main.cpp.o: CMakeFiles/crow_demo.dir/flags.make
CMakeFiles/crow_demo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/src/cppweb/crow_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/crow_demo.dir/main.cpp.o"
	/usr/local/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crow_demo.dir/main.cpp.o -c /usr/src/cppweb/crow_demo/main.cpp

CMakeFiles/crow_demo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crow_demo.dir/main.cpp.i"
	/usr/local/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/src/cppweb/crow_demo/main.cpp > CMakeFiles/crow_demo.dir/main.cpp.i

CMakeFiles/crow_demo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crow_demo.dir/main.cpp.s"
	/usr/local/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/src/cppweb/crow_demo/main.cpp -o CMakeFiles/crow_demo.dir/main.cpp.s

CMakeFiles/crow_demo.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/crow_demo.dir/main.cpp.o.requires

CMakeFiles/crow_demo.dir/main.cpp.o.provides: CMakeFiles/crow_demo.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/crow_demo.dir/build.make CMakeFiles/crow_demo.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/crow_demo.dir/main.cpp.o.provides

CMakeFiles/crow_demo.dir/main.cpp.o.provides.build: CMakeFiles/crow_demo.dir/main.cpp.o


# Object files for target crow_demo
crow_demo_OBJECTS = \
"CMakeFiles/crow_demo.dir/main.cpp.o"

# External object files for target crow_demo
crow_demo_EXTERNAL_OBJECTS =

crow_demo: CMakeFiles/crow_demo.dir/main.cpp.o
crow_demo: CMakeFiles/crow_demo.dir/build.make
crow_demo: /usr/lib/x86_64-linux-gnu/libboost_system.so
crow_demo: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
crow_demo: CMakeFiles/crow_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/usr/src/cppweb/crow_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable crow_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crow_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crow_demo.dir/build: crow_demo

.PHONY : CMakeFiles/crow_demo.dir/build

CMakeFiles/crow_demo.dir/requires: CMakeFiles/crow_demo.dir/main.cpp.o.requires

.PHONY : CMakeFiles/crow_demo.dir/requires

CMakeFiles/crow_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crow_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crow_demo.dir/clean

CMakeFiles/crow_demo.dir/depend:
	cd /usr/src/cppweb/crow_demo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/src/cppweb/crow_demo /usr/src/cppweb/crow_demo /usr/src/cppweb/crow_demo/build /usr/src/cppweb/crow_demo/build /usr/src/cppweb/crow_demo/build/CMakeFiles/crow_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crow_demo.dir/depend

