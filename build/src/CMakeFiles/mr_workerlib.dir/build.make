# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /home/stanley/Desktop/vcpkg/downloads/tools/cmake-3.18.4-linux/cmake-3.18.4-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/stanley/Desktop/vcpkg/downloads/tools/cmake-3.18.4-linux/cmake-3.18.4-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stanley/Desktop/aos_p4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stanley/Desktop/aos_p4/build

# Include any dependencies generated for this target.
include src/CMakeFiles/mr_workerlib.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mr_workerlib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mr_workerlib.dir/flags.make

src/CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.o: src/CMakeFiles/mr_workerlib.dir/flags.make
src/CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.o: ../src/mr_task_factory.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stanley/Desktop/aos_p4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.o"
	cd /home/stanley/Desktop/aos_p4/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.o -c /home/stanley/Desktop/aos_p4/src/mr_task_factory.cc

src/CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.i"
	cd /home/stanley/Desktop/aos_p4/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stanley/Desktop/aos_p4/src/mr_task_factory.cc > CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.i

src/CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.s"
	cd /home/stanley/Desktop/aos_p4/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stanley/Desktop/aos_p4/src/mr_task_factory.cc -o CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.s

src/CMakeFiles/mr_workerlib.dir/run_worker.cc.o: src/CMakeFiles/mr_workerlib.dir/flags.make
src/CMakeFiles/mr_workerlib.dir/run_worker.cc.o: ../src/run_worker.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stanley/Desktop/aos_p4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/mr_workerlib.dir/run_worker.cc.o"
	cd /home/stanley/Desktop/aos_p4/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mr_workerlib.dir/run_worker.cc.o -c /home/stanley/Desktop/aos_p4/src/run_worker.cc

src/CMakeFiles/mr_workerlib.dir/run_worker.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mr_workerlib.dir/run_worker.cc.i"
	cd /home/stanley/Desktop/aos_p4/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stanley/Desktop/aos_p4/src/run_worker.cc > CMakeFiles/mr_workerlib.dir/run_worker.cc.i

src/CMakeFiles/mr_workerlib.dir/run_worker.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mr_workerlib.dir/run_worker.cc.s"
	cd /home/stanley/Desktop/aos_p4/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stanley/Desktop/aos_p4/src/run_worker.cc -o CMakeFiles/mr_workerlib.dir/run_worker.cc.s

# Object files for target mr_workerlib
mr_workerlib_OBJECTS = \
"CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.o" \
"CMakeFiles/mr_workerlib.dir/run_worker.cc.o"

# External object files for target mr_workerlib
mr_workerlib_EXTERNAL_OBJECTS =

src/libmr_workerlib.a: src/CMakeFiles/mr_workerlib.dir/mr_task_factory.cc.o
src/libmr_workerlib.a: src/CMakeFiles/mr_workerlib.dir/run_worker.cc.o
src/libmr_workerlib.a: src/CMakeFiles/mr_workerlib.dir/build.make
src/libmr_workerlib.a: src/CMakeFiles/mr_workerlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stanley/Desktop/aos_p4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libmr_workerlib.a"
	cd /home/stanley/Desktop/aos_p4/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mr_workerlib.dir/cmake_clean_target.cmake
	cd /home/stanley/Desktop/aos_p4/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mr_workerlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mr_workerlib.dir/build: src/libmr_workerlib.a

.PHONY : src/CMakeFiles/mr_workerlib.dir/build

src/CMakeFiles/mr_workerlib.dir/clean:
	cd /home/stanley/Desktop/aos_p4/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mr_workerlib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mr_workerlib.dir/clean

src/CMakeFiles/mr_workerlib.dir/depend:
	cd /home/stanley/Desktop/aos_p4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stanley/Desktop/aos_p4 /home/stanley/Desktop/aos_p4/src /home/stanley/Desktop/aos_p4/build /home/stanley/Desktop/aos_p4/build/src /home/stanley/Desktop/aos_p4/build/src/CMakeFiles/mr_workerlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mr_workerlib.dir/depend

