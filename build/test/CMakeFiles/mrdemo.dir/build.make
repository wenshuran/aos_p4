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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wenshuran/Desktop/aos_p4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wenshuran/Desktop/aos_p4/build

# Include any dependencies generated for this target.
include test/CMakeFiles/mrdemo.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/mrdemo.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/mrdemo.dir/flags.make

test/CMakeFiles/mrdemo.dir/main.cc.o: test/CMakeFiles/mrdemo.dir/flags.make
test/CMakeFiles/mrdemo.dir/main.cc.o: ../test/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wenshuran/Desktop/aos_p4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/mrdemo.dir/main.cc.o"
	cd /home/wenshuran/Desktop/aos_p4/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mrdemo.dir/main.cc.o -c /home/wenshuran/Desktop/aos_p4/test/main.cc

test/CMakeFiles/mrdemo.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mrdemo.dir/main.cc.i"
	cd /home/wenshuran/Desktop/aos_p4/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wenshuran/Desktop/aos_p4/test/main.cc > CMakeFiles/mrdemo.dir/main.cc.i

test/CMakeFiles/mrdemo.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mrdemo.dir/main.cc.s"
	cd /home/wenshuran/Desktop/aos_p4/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wenshuran/Desktop/aos_p4/test/main.cc -o CMakeFiles/mrdemo.dir/main.cc.s

# Object files for target mrdemo
mrdemo_OBJECTS = \
"CMakeFiles/mrdemo.dir/main.cc.o"

# External object files for target mrdemo
mrdemo_EXTERNAL_OBJECTS =

bin/mrdemo: test/CMakeFiles/mrdemo.dir/main.cc.o
bin/mrdemo: test/CMakeFiles/mrdemo.dir/build.make
bin/mrdemo: src/libmapreducelib.a
bin/mrdemo: src/libp4protolib.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libgrpc++.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libprotobufd.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libgrpc.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libssl.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libcrypto.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libz.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libcares.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libre2.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libupb.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libport.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_status.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_cord.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_hash.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_bad_variant_access.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_city.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_raw_hash_set.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_bad_optional_access.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_hashtablez_sampler.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_exponential_biased.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libgpr.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_synchronization.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_stacktrace.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_symbolize.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_debugging_internal.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_demangle_internal.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_graphcycles_internal.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_time.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_civil_time.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_time_zone.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_malloc_internal.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_str_format_internal.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_strings.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_strings_internal.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_int128.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_throw_delegate.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_base.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_raw_logging_internal.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_log_severity.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libabsl_spinlock_wait.a
bin/mrdemo: /home/wenshuran/Desktop/vcpkg/installed/x64-linux/debug/lib/libaddress_sorting.a
bin/mrdemo: test/CMakeFiles/mrdemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wenshuran/Desktop/aos_p4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/mrdemo"
	cd /home/wenshuran/Desktop/aos_p4/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mrdemo.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "symbolic link /home/wenshuran/Desktop/aos_p4/build/bin/config.ini created."
	cd /home/wenshuran/Desktop/aos_p4/build/test && /usr/local/bin/cmake -E create_symlink /home/wenshuran/Desktop/aos_p4/test/config.ini /home/wenshuran/Desktop/aos_p4/build/bin/config.ini

# Rule to build all files generated by this target.
test/CMakeFiles/mrdemo.dir/build: bin/mrdemo

.PHONY : test/CMakeFiles/mrdemo.dir/build

test/CMakeFiles/mrdemo.dir/clean:
	cd /home/wenshuran/Desktop/aos_p4/build/test && $(CMAKE_COMMAND) -P CMakeFiles/mrdemo.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/mrdemo.dir/clean

test/CMakeFiles/mrdemo.dir/depend:
	cd /home/wenshuran/Desktop/aos_p4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wenshuran/Desktop/aos_p4 /home/wenshuran/Desktop/aos_p4/test /home/wenshuran/Desktop/aos_p4/build /home/wenshuran/Desktop/aos_p4/build/test /home/wenshuran/Desktop/aos_p4/build/test/CMakeFiles/mrdemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/mrdemo.dir/depend

