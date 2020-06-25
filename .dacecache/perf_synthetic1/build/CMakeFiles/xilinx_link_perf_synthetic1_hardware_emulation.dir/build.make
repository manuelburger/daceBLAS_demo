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

# Utility rule file for xilinx_link_perf_synthetic1_hardware_emulation.

# Include the progress variables for this target.
include CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/progress.make

CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation: perf_synthetic1_hw_emu.xclbin


perf_synthetic1_hw_emu.xclbin: perf_synthetic1_hw_emu.xo
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating perf_synthetic1_hw_emu.xclbin"
	XILINX_PATH=/home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build /opt/Xilinx/Vitis/2019.2/bin/v++ -s -O3 -I/home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen/include -I/home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen/../external/hlslib/include -I/home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen/../runtime/include -I/home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build --platform xilinx_u250_xdma_201830_2 --kernel_frequency 200 --advanced.prop kernel.test_state.kernel_flags="-std=c++11\ -DDACE_SYNTHESIS\ -DDACE_XILINX\ -DDACE_XILINX_DEVICE_CODE\ -DHLSLIB_SYNTHESIS\ -std=c++11" --sp test_state_1.m_axi_gmem0:DDR[0] --sp test_state_1.m_axi_gmem1:DDR[3] --sp test_state_1.m_axi_gmem2:DDR[1] --sp test_state_1.m_axi_gmem3:DDR[2] --sp test_state_1.m_axi_gmem4:DDR[2] --sp test_state_1.m_axi_gmem5:DDR[2] --sp test_state_1.m_axi_gmem6:DDR[2] --sp test_state_1.m_axi_gmem7:DDR[2] --sp test_state_1.m_axi_gmem8:DDR[2] --sp test_state_1.m_axi_gmem9:DDR[2] --sp test_state_1.m_axi_gmem10:DDR[2] --sp test_state_1.m_axi_gmem11:DDR[0] --kernel test_state -l -t hw_emu perf_synthetic1_hw_emu.xo -o perf_synthetic1_hw_emu.xclbin

perf_synthetic1_hw_emu.xo: /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/src/xilinx/device/test_state.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating perf_synthetic1_hw_emu.xo"
	XILINX_PATH=/home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build /opt/Xilinx/Vitis/2019.2/bin/v++ -s -O3 -I/home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen/include -I/home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen/../external/hlslib/include -I/home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen/../runtime/include -I/home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build --platform xilinx_u250_xdma_201830_2 --kernel_frequency 200 --advanced.prop kernel.test_state.kernel_flags="-std=c++11\ -DDACE_SYNTHESIS\ -DDACE_XILINX\ -DDACE_XILINX_DEVICE_CODE\ -DHLSLIB_SYNTHESIS\ -std=c++11" --sp test_state_1.m_axi_gmem0:DDR[0] --sp test_state_1.m_axi_gmem1:DDR[3] --sp test_state_1.m_axi_gmem2:DDR[1] --sp test_state_1.m_axi_gmem3:DDR[2] --sp test_state_1.m_axi_gmem4:DDR[2] --sp test_state_1.m_axi_gmem5:DDR[2] --sp test_state_1.m_axi_gmem6:DDR[2] --sp test_state_1.m_axi_gmem7:DDR[2] --sp test_state_1.m_axi_gmem8:DDR[2] --sp test_state_1.m_axi_gmem9:DDR[2] --sp test_state_1.m_axi_gmem10:DDR[2] --sp test_state_1.m_axi_gmem11:DDR[0] --kernel test_state -c -t hw_emu /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/src/xilinx/device/test_state.cpp -o perf_synthetic1_hw_emu.xo

xilinx_link_perf_synthetic1_hardware_emulation: CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation
xilinx_link_perf_synthetic1_hardware_emulation: perf_synthetic1_hw_emu.xclbin
xilinx_link_perf_synthetic1_hardware_emulation: perf_synthetic1_hw_emu.xo
xilinx_link_perf_synthetic1_hardware_emulation: CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/build.make

.PHONY : xilinx_link_perf_synthetic1_hardware_emulation

# Rule to build all files generated by this target.
CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/build: xilinx_link_perf_synthetic1_hardware_emulation

.PHONY : CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/build

CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/clean

CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/depend:
	cd /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen /home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build /home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build/CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/xilinx_link_perf_synthetic1_hardware_emulation.dir/depend

