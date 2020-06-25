#include "dace/xilinx/host.h"
#include "dace/dace.h"
#include <iostream>


dace::fpga::Context *dace::fpga::_context;

DACE_EXPORTED int __dace_init_xilinx(float * __restrict__ A_ger, float * __restrict__ res, float * __restrict__ x_gemv, float * __restrict__ x_ger, float * __restrict__ y1_ger, float * __restrict__ y2_ger, float * __restrict__ y3_ger, float * __restrict__ y4_ger, float * __restrict__ y5_ger, float * __restrict__ y6_ger, float * __restrict__ y7_ger, float * __restrict__ y8_ger, float a, int n) {
    dace::unset_environment_variable("XCL_EMULATION_MODE");
    dace::unset_environment_variable("XILINX_SDX");
    
    dace::fpga::_context = new dace::fpga::Context();
    dace::fpga::_context->Get().MakeProgram(DACE_BINARY_DIR "/perf_synthetic1_hw.xclbin");
    return 0;
}

DACE_EXPORTED void __dace_exit_xilinx(float * __restrict__ A_ger, float * __restrict__ res, float * __restrict__ x_gemv, float * __restrict__ x_ger, float * __restrict__ y1_ger, float * __restrict__ y2_ger, float * __restrict__ y3_ger, float * __restrict__ y4_ger, float * __restrict__ y5_ger, float * __restrict__ y6_ger, float * __restrict__ y7_ger, float * __restrict__ y8_ger, float a, int n) {
    delete dace::fpga::_context;
}

///////////////////////////////////////////////////////////////////////////////
// Kernel: test_state
///////////////////////////////////////////////////////////////////////////////

// Signature of kernel function (with raw pointers) for argument matching
DACE_EXPORTED void test_state(float * __restrict__ f_A_ger_in, float * __restrict__ f_x_gemv_in, float * __restrict__ f_x_ger_in, float * __restrict__ f_y1_ger_in, float * __restrict__ f_y2_ger_in, float * __restrict__ f_y3_ger_in, float * __restrict__ f_y4_ger_in, float * __restrict__ f_y5_ger_in, float * __restrict__ f_y6_ger_in, float * __restrict__ f_y7_ger_in, float * __restrict__ f_y8_ger_in, float * __restrict__ fpga_res_out, float a, int n);

DACE_EXPORTED void __dace_runkernel_test_state(hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_A_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_x_gemv, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_x_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y1_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y2_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y3_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y4_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y5_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y6_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y7_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y8_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &fpga_res, float a, int n) {
    hlslib::ocl::Program program = dace::fpga::_context->Get().CurrentlyLoadedProgram();
    auto kernel = program.MakeKernel(test_state, "test_state", f_A_ger, f_x_gemv, f_x_ger, f_y1_ger, f_y2_ger, f_y3_ger, f_y4_ger, f_y5_ger, f_y6_ger, f_y7_ger, f_y8_ger, fpga_res, a, n);
    const std::pair<double, double> elapsed = kernel.ExecuteTask();
    std::cout << "Kernel executed in " << elapsed.second << " seconds.\n" << std::flush;
}


