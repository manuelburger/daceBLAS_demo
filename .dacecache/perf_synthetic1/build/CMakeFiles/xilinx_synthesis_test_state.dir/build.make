# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build

# Utility rule file for xilinx_synthesis_test_state.

# Include the progress variables for this target.
include CMakeFiles/xilinx_synthesis_test_state.dir/progress.make

CMakeFiles/xilinx_synthesis_test_state:
	/opt/Xilinx/Vivado/2019.2/bin/vivado_hls -f Synthesize_test_state.tcl

xilinx_synthesis_test_state: CMakeFiles/xilinx_synthesis_test_state
xilinx_synthesis_test_state: CMakeFiles/xilinx_synthesis_test_state.dir/build.make

.PHONY : xilinx_synthesis_test_state

# Rule to build all files generated by this target.
CMakeFiles/xilinx_synthesis_test_state.dir/build: xilinx_synthesis_test_state

.PHONY : CMakeFiles/xilinx_synthesis_test_state.dir/build

CMakeFiles/xilinx_synthesis_test_state.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/xilinx_synthesis_test_state.dir/cmake_clean.cmake
.PHONY : CMakeFiles/xilinx_synthesis_test_state.dir/clean

CMakeFiles/xilinx_synthesis_test_state.dir/depend:
	cd /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen /home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build/CMakeFiles/xilinx_synthesis_test_state.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/xilinx_synthesis_test_state.dir/depend

