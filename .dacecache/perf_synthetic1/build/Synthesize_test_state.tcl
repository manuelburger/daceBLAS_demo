open_project test_state 
open_solution xcu280-fsvh2892-2L-e  
add_files -cflags "-std=c++11 -DDACE_SYNTHESIS -DDACE_XILINX -DDACE_XILINX_DEVICE_CODE -DHLSLIB_SYNTHESIS -std=c++11 -I/home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen/../runtime/include -I/home/burgerm/daceBLAS_demo/daceEnv/lib/python3.6/site-packages/dace/codegen/../external/hlslib/include -I/home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/build" "/home/burgerm/daceBLAS_demo/.dacecache/perf_synthetic1/src/xilinx/device/test_state.cpp" 
set_top test_state 
set_part xcu280-fsvh2892-2L-e 
create_clock -period 200MHz -name default
# SDAccel default options
config_rtl -register_reset
config_interface -m_axi_addr64
config_schedule -relax_ii_for_timing
config_compile -pipeline_loops 64
config_compile -name_max_length 256
csynth_design
exit
