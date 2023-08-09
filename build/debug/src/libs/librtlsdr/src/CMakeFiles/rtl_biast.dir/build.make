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
CMAKE_SOURCE_DIR = /home/ann/WORK/work_qt/radio_receiver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ann/WORK/work_qt/radio_receiver/build/debug

# Include any dependencies generated for this target.
include src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/compiler_depend.make

# Include the progress variables for this target.
include src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/progress.make

# Include the compile flags for this target's objects.
include src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/flags.make

src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/rtl_biast.c.o: src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/flags.make
src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/rtl_biast.c.o: ../../src/libs/librtlsdr/src/rtl_biast.c
src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/rtl_biast.c.o: src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ann/WORK/work_qt/radio_receiver/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/rtl_biast.c.o"
	cd /home/ann/WORK/work_qt/radio_receiver/build/debug/src/libs/librtlsdr/src && /usr/bin/afl-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/rtl_biast.c.o -MF CMakeFiles/rtl_biast.dir/rtl_biast.c.o.d -o CMakeFiles/rtl_biast.dir/rtl_biast.c.o -c /home/ann/WORK/work_qt/radio_receiver/src/libs/librtlsdr/src/rtl_biast.c

src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/rtl_biast.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtl_biast.dir/rtl_biast.c.i"
	cd /home/ann/WORK/work_qt/radio_receiver/build/debug/src/libs/librtlsdr/src && /usr/bin/afl-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ann/WORK/work_qt/radio_receiver/src/libs/librtlsdr/src/rtl_biast.c > CMakeFiles/rtl_biast.dir/rtl_biast.c.i

src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/rtl_biast.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtl_biast.dir/rtl_biast.c.s"
	cd /home/ann/WORK/work_qt/radio_receiver/build/debug/src/libs/librtlsdr/src && /usr/bin/afl-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ann/WORK/work_qt/radio_receiver/src/libs/librtlsdr/src/rtl_biast.c -o CMakeFiles/rtl_biast.dir/rtl_biast.c.s

# Object files for target rtl_biast
rtl_biast_OBJECTS = \
"CMakeFiles/rtl_biast.dir/rtl_biast.c.o"

# External object files for target rtl_biast
rtl_biast_EXTERNAL_OBJECTS =

src/libs/librtlsdr/src/rtl_biast: src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/rtl_biast.c.o
src/libs/librtlsdr/src/rtl_biast: src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/build.make
src/libs/librtlsdr/src/rtl_biast: src/libs/librtlsdr/src/librtlsdr.so.0.8git
src/libs/librtlsdr/src/rtl_biast: src/libs/librtlsdr/src/libconvenience_static.a
src/libs/librtlsdr/src/rtl_biast: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
src/libs/librtlsdr/src/rtl_biast: src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ann/WORK/work_qt/radio_receiver/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable rtl_biast"
	cd /home/ann/WORK/work_qt/radio_receiver/build/debug/src/libs/librtlsdr/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rtl_biast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/build: src/libs/librtlsdr/src/rtl_biast
.PHONY : src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/build

src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/clean:
	cd /home/ann/WORK/work_qt/radio_receiver/build/debug/src/libs/librtlsdr/src && $(CMAKE_COMMAND) -P CMakeFiles/rtl_biast.dir/cmake_clean.cmake
.PHONY : src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/clean

src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/depend:
	cd /home/ann/WORK/work_qt/radio_receiver/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ann/WORK/work_qt/radio_receiver /home/ann/WORK/work_qt/radio_receiver/src/libs/librtlsdr/src /home/ann/WORK/work_qt/radio_receiver/build/debug /home/ann/WORK/work_qt/radio_receiver/build/debug/src/libs/librtlsdr/src /home/ann/WORK/work_qt/radio_receiver/build/debug/src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/libs/librtlsdr/src/CMakeFiles/rtl_biast.dir/depend

