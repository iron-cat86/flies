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

# Include any dependencies generated for this target.
include mainwindow/CMakeFiles/mainwindow.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mainwindow/CMakeFiles/mainwindow.dir/compiler_depend.make

# Include the progress variables for this target.
include mainwindow/CMakeFiles/mainwindow.dir/progress.make

# Include the compile flags for this target's objects.
include mainwindow/CMakeFiles/mainwindow.dir/flags.make

mainwindow/CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.o: mainwindow/CMakeFiles/mainwindow.dir/flags.make
mainwindow/CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.o: mainwindow/mainwindow_autogen/mocs_compilation.cpp
mainwindow/CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.o: mainwindow/CMakeFiles/mainwindow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bel/work/flies/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mainwindow/CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.o"
	cd /home/bel/work/flies/build/mainwindow && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mainwindow/CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.o -MF CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.o -c /home/bel/work/flies/build/mainwindow/mainwindow_autogen/mocs_compilation.cpp

mainwindow/CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.i"
	cd /home/bel/work/flies/build/mainwindow && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bel/work/flies/build/mainwindow/mainwindow_autogen/mocs_compilation.cpp > CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.i

mainwindow/CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.s"
	cd /home/bel/work/flies/build/mainwindow && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bel/work/flies/build/mainwindow/mainwindow_autogen/mocs_compilation.cpp -o CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.s

mainwindow/CMakeFiles/mainwindow.dir/mainwindow.cpp.o: mainwindow/CMakeFiles/mainwindow.dir/flags.make
mainwindow/CMakeFiles/mainwindow.dir/mainwindow.cpp.o: /home/bel/work/flies/mainwindow/mainwindow.cpp
mainwindow/CMakeFiles/mainwindow.dir/mainwindow.cpp.o: mainwindow/CMakeFiles/mainwindow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bel/work/flies/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object mainwindow/CMakeFiles/mainwindow.dir/mainwindow.cpp.o"
	cd /home/bel/work/flies/build/mainwindow && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mainwindow/CMakeFiles/mainwindow.dir/mainwindow.cpp.o -MF CMakeFiles/mainwindow.dir/mainwindow.cpp.o.d -o CMakeFiles/mainwindow.dir/mainwindow.cpp.o -c /home/bel/work/flies/mainwindow/mainwindow.cpp

mainwindow/CMakeFiles/mainwindow.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mainwindow.dir/mainwindow.cpp.i"
	cd /home/bel/work/flies/build/mainwindow && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bel/work/flies/mainwindow/mainwindow.cpp > CMakeFiles/mainwindow.dir/mainwindow.cpp.i

mainwindow/CMakeFiles/mainwindow.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mainwindow.dir/mainwindow.cpp.s"
	cd /home/bel/work/flies/build/mainwindow && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bel/work/flies/mainwindow/mainwindow.cpp -o CMakeFiles/mainwindow.dir/mainwindow.cpp.s

# Object files for target mainwindow
mainwindow_OBJECTS = \
"CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/mainwindow.dir/mainwindow.cpp.o"

# External object files for target mainwindow
mainwindow_EXTERNAL_OBJECTS =

mainwindow/libmainwindow.a: mainwindow/CMakeFiles/mainwindow.dir/mainwindow_autogen/mocs_compilation.cpp.o
mainwindow/libmainwindow.a: mainwindow/CMakeFiles/mainwindow.dir/mainwindow.cpp.o
mainwindow/libmainwindow.a: mainwindow/CMakeFiles/mainwindow.dir/build.make
mainwindow/libmainwindow.a: mainwindow/CMakeFiles/mainwindow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bel/work/flies/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libmainwindow.a"
	cd /home/bel/work/flies/build/mainwindow && $(CMAKE_COMMAND) -P CMakeFiles/mainwindow.dir/cmake_clean_target.cmake
	cd /home/bel/work/flies/build/mainwindow && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mainwindow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mainwindow/CMakeFiles/mainwindow.dir/build: mainwindow/libmainwindow.a
.PHONY : mainwindow/CMakeFiles/mainwindow.dir/build

mainwindow/CMakeFiles/mainwindow.dir/clean:
	cd /home/bel/work/flies/build/mainwindow && $(CMAKE_COMMAND) -P CMakeFiles/mainwindow.dir/cmake_clean.cmake
.PHONY : mainwindow/CMakeFiles/mainwindow.dir/clean

mainwindow/CMakeFiles/mainwindow.dir/depend:
	cd /home/bel/work/flies/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bel/work/flies /home/bel/work/flies/mainwindow /home/bel/work/flies/build /home/bel/work/flies/build/mainwindow /home/bel/work/flies/build/mainwindow/CMakeFiles/mainwindow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mainwindow/CMakeFiles/mainwindow.dir/depend
