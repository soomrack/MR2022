# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ATD.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ATD.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ATD.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ATD.dir/flags.make

CMakeFiles/ATD.dir/main.cpp.o: CMakeFiles/ATD.dir/flags.make
CMakeFiles/ATD.dir/main.cpp.o: ../main.cpp
CMakeFiles/ATD.dir/main.cpp.o: CMakeFiles/ATD.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ATD.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ATD.dir/main.cpp.o -MF CMakeFiles/ATD.dir/main.cpp.o.d -o CMakeFiles/ATD.dir/main.cpp.o -c /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/main.cpp

CMakeFiles/ATD.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATD.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/main.cpp > CMakeFiles/ATD.dir/main.cpp.i

CMakeFiles/ATD.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATD.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/main.cpp -o CMakeFiles/ATD.dir/main.cpp.s

# Object files for target ATD
ATD_OBJECTS = \
"CMakeFiles/ATD.dir/main.cpp.o"

# External object files for target ATD
ATD_EXTERNAL_OBJECTS =

ATD: CMakeFiles/ATD.dir/main.cpp.o
ATD: CMakeFiles/ATD.dir/build.make
ATD: CMakeFiles/ATD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ATD"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ATD.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ATD.dir/build: ATD
.PHONY : CMakeFiles/ATD.dir/build

CMakeFiles/ATD.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ATD.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ATD.dir/clean

CMakeFiles/ATD.dir/depend:
	cd /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/cmake-build-debug /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/cmake-build-debug /mnt/c/Users/sirbo/CLionProjects/MR2022/Boyko_Alexander/ATD/cmake-build-debug/CMakeFiles/ATD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ATD.dir/depend

