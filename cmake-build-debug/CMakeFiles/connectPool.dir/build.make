# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/connectPool.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/connectPool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/connectPool.dir/flags.make

CMakeFiles/connectPool.dir/mySQLConn.cpp.o: CMakeFiles/connectPool.dir/flags.make
CMakeFiles/connectPool.dir/mySQLConn.cpp.o: ../mySQLConn.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/connectPool.dir/mySQLConn.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/connectPool.dir/mySQLConn.cpp.o -c /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/mySQLConn.cpp

CMakeFiles/connectPool.dir/mySQLConn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connectPool.dir/mySQLConn.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/mySQLConn.cpp > CMakeFiles/connectPool.dir/mySQLConn.cpp.i

CMakeFiles/connectPool.dir/mySQLConn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connectPool.dir/mySQLConn.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/mySQLConn.cpp -o CMakeFiles/connectPool.dir/mySQLConn.cpp.s

CMakeFiles/connectPool.dir/connectionPool.cpp.o: CMakeFiles/connectPool.dir/flags.make
CMakeFiles/connectPool.dir/connectionPool.cpp.o: ../connectionPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/connectPool.dir/connectionPool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/connectPool.dir/connectionPool.cpp.o -c /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/connectionPool.cpp

CMakeFiles/connectPool.dir/connectionPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connectPool.dir/connectionPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/connectionPool.cpp > CMakeFiles/connectPool.dir/connectionPool.cpp.i

CMakeFiles/connectPool.dir/connectionPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connectPool.dir/connectionPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/connectionPool.cpp -o CMakeFiles/connectPool.dir/connectionPool.cpp.s

CMakeFiles/connectPool.dir/jsoncpp.cpp.o: CMakeFiles/connectPool.dir/flags.make
CMakeFiles/connectPool.dir/jsoncpp.cpp.o: ../jsoncpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/connectPool.dir/jsoncpp.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/connectPool.dir/jsoncpp.cpp.o -c /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/jsoncpp.cpp

CMakeFiles/connectPool.dir/jsoncpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connectPool.dir/jsoncpp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/jsoncpp.cpp > CMakeFiles/connectPool.dir/jsoncpp.cpp.i

CMakeFiles/connectPool.dir/jsoncpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connectPool.dir/jsoncpp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/jsoncpp.cpp -o CMakeFiles/connectPool.dir/jsoncpp.cpp.s

CMakeFiles/connectPool.dir/main.cpp.o: CMakeFiles/connectPool.dir/flags.make
CMakeFiles/connectPool.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/connectPool.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/connectPool.dir/main.cpp.o -c /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/main.cpp

CMakeFiles/connectPool.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/connectPool.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/main.cpp > CMakeFiles/connectPool.dir/main.cpp.i

CMakeFiles/connectPool.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/connectPool.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/main.cpp -o CMakeFiles/connectPool.dir/main.cpp.s

# Object files for target connectPool
connectPool_OBJECTS = \
"CMakeFiles/connectPool.dir/mySQLConn.cpp.o" \
"CMakeFiles/connectPool.dir/connectionPool.cpp.o" \
"CMakeFiles/connectPool.dir/jsoncpp.cpp.o" \
"CMakeFiles/connectPool.dir/main.cpp.o"

# External object files for target connectPool
connectPool_EXTERNAL_OBJECTS =

connectPool: CMakeFiles/connectPool.dir/mySQLConn.cpp.o
connectPool: CMakeFiles/connectPool.dir/connectionPool.cpp.o
connectPool: CMakeFiles/connectPool.dir/jsoncpp.cpp.o
connectPool: CMakeFiles/connectPool.dir/main.cpp.o
connectPool: CMakeFiles/connectPool.dir/build.make
connectPool: CMakeFiles/connectPool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable connectPool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/connectPool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/connectPool.dir/build: connectPool
.PHONY : CMakeFiles/connectPool.dir/build

CMakeFiles/connectPool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/connectPool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/connectPool.dir/clean

CMakeFiles/connectPool.dir/depend:
	cd /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3 /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3 /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug /home/kendrick/clion_project/temp/tmp/tmp.my764gGDy3/cmake-build-debug/CMakeFiles/connectPool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/connectPool.dir/depend
