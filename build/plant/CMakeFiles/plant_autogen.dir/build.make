# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bel/work/flies

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bel/work/flies/build

# Utility rule file for plant_autogen.

# Include any custom commands dependencies for this target.
include plant/CMakeFiles/plant_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include plant/CMakeFiles/plant_autogen.dir/progress.make

plant/CMakeFiles/plant_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/bel/work/flies/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target plant"
	cd /home/bel/work/flies/build/plant && /usr/bin/cmake -E cmake_autogen /home/bel/work/flies/build/plant/CMakeFiles/plant_autogen.dir/AutogenInfo.json RelWithDebInfo

plant_autogen: plant/CMakeFiles/plant_autogen
plant_autogen: plant/CMakeFiles/plant_autogen.dir/build.make
.PHONY : plant_autogen

# Rule to build all files generated by this target.
plant/CMakeFiles/plant_autogen.dir/build: plant_autogen
.PHONY : plant/CMakeFiles/plant_autogen.dir/build

plant/CMakeFiles/plant_autogen.dir/clean:
	cd /home/bel/work/flies/build/plant && $(CMAKE_COMMAND) -P CMakeFiles/plant_autogen.dir/cmake_clean.cmake
.PHONY : plant/CMakeFiles/plant_autogen.dir/clean

plant/CMakeFiles/plant_autogen.dir/depend:
	cd /home/bel/work/flies/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bel/work/flies /home/bel/work/flies/plant /home/bel/work/flies/build /home/bel/work/flies/build/plant /home/bel/work/flies/build/plant/CMakeFiles/plant_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plant/CMakeFiles/plant_autogen.dir/depend
