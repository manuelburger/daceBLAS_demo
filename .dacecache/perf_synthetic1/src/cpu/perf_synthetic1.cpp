/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>



DACE_EXPORTED void __dace_runkernel_test_state(hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_A_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_x_gemv, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_x_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y1_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y2_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y3_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y4_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y5_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y6_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y7_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &f_y8_ger, hlslib::ocl::Buffer<float, hlslib::ocl::Access::readWrite> &fpga_res, float a, int n);

void __program_perf_synthetic1_internal(float * __restrict__ A_ger, float * __restrict__ res, float * __restrict__ x_gemv, float * __restrict__ x_ger, float * __restrict__ y1_ger, float * __restrict__ y2_ger, float * __restrict__ y3_ger, float * __restrict__ y4_ger, float * __restrict__ y5_ger, float * __restrict__ y6_ger, float * __restrict__ y7_ger, float * __restrict__ y8_ger, float a, int n)
{
    auto f_A_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank0, (n * n));
    auto f_x_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank1, n);
    auto f_y1_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank2, n);
    auto f_y2_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank2, n);
    auto f_y3_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank2, n);
    auto f_y4_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank2, n);
    auto f_y5_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank2, n);
    auto f_y6_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank2, n);
    auto f_y7_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank2, n);
    auto f_y8_ger = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank2, n);
    auto f_x_gemv = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank3, n);
    auto fpga_res = dace::fpga::_context->Get().MakeBuffer<float, hlslib::ocl::Access::readWrite>(hlslib::ocl::MemoryBank::bank0, 1);

    __state_perf_synthetic1_copyToFPGA:
    {
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                f_A_ger.CopyFromHost(0, (n * n), A_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_x_ger.CopyFromHost(0, n, x_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_y1_ger.CopyFromHost(0, n, y1_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_y2_ger.CopyFromHost(0, n, y2_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_y3_ger.CopyFromHost(0, n, y3_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_y4_ger.CopyFromHost(0, n, y4_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_y5_ger.CopyFromHost(0, n, y5_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_y6_ger.CopyFromHost(0, n, y6_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_y7_ger.CopyFromHost(0, n, y7_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_y8_ger.CopyFromHost(0, n, y8_ger + 0);
            } // End omp section
            #pragma omp section
            {
                f_x_gemv.CopyFromHost(0, n, x_gemv + 0);
            } // End omp section
        } // End omp sections
    }
    __state_perf_synthetic1_test_state:
    {
        __dace_runkernel_test_state(f_A_ger, f_x_gemv, f_x_ger, f_y1_ger, f_y2_ger, f_y3_ger, f_y4_ger, f_y5_ger, f_y6_ger, f_y7_ger, f_y8_ger, fpga_res, a, n);
    }
    __state_perf_synthetic1_copyToCPU:
    {
        fpga_res.CopyToHost(0, 1, res + 0);
    }
    __state_exit_perf_synthetic1_sdfg:;
}

DACE_EXPORTED void __program_perf_synthetic1(float * __restrict__ A_ger, float * __restrict__ res, float * __restrict__ x_gemv, float * __restrict__ x_ger, float * __restrict__ y1_ger, float * __restrict__ y2_ger, float * __restrict__ y3_ger, float * __restrict__ y4_ger, float * __restrict__ y5_ger, float * __restrict__ y6_ger, float * __restrict__ y7_ger, float * __restrict__ y8_ger, float a, int n)
{
    __program_perf_synthetic1_internal(A_ger, res, x_gemv, x_ger, y1_ger, y2_ger, y3_ger, y4_ger, y5_ger, y6_ger, y7_ger, y8_ger, a, n);
}
DACE_EXPORTED int __dace_init_xilinx(float * __restrict__ A_ger, float * __restrict__ res, float * __restrict__ x_gemv, float * __restrict__ x_ger, float * __restrict__ y1_ger, float * __restrict__ y2_ger, float * __restrict__ y3_ger, float * __restrict__ y4_ger, float * __restrict__ y5_ger, float * __restrict__ y6_ger, float * __restrict__ y7_ger, float * __restrict__ y8_ger, float a, int n);

DACE_EXPORTED int __dace_init_perf_synthetic1(float * __restrict__ A_ger, float * __restrict__ res, float * __restrict__ x_gemv, float * __restrict__ x_ger, float * __restrict__ y1_ger, float * __restrict__ y2_ger, float * __restrict__ y3_ger, float * __restrict__ y4_ger, float * __restrict__ y5_ger, float * __restrict__ y6_ger, float * __restrict__ y7_ger, float * __restrict__ y8_ger, float a, int n)
{
    int __result = 0;
    __result |= __dace_init_xilinx(A_ger, res, x_gemv, x_ger, y1_ger, y2_ger, y3_ger, y4_ger, y5_ger, y6_ger, y7_ger, y8_ger, a, n);

    return __result;
}

DACE_EXPORTED void __dace_exit_perf_synthetic1(float * __restrict__ A_ger, float * __restrict__ res, float * __restrict__ x_gemv, float * __restrict__ x_ger, float * __restrict__ y1_ger, float * __restrict__ y2_ger, float * __restrict__ y3_ger, float * __restrict__ y4_ger, float * __restrict__ y5_ger, float * __restrict__ y6_ger, float * __restrict__ y7_ger, float * __restrict__ y8_ger, float a, int n)
{
}
