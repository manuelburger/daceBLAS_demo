# BLAS for FPGA based on the DaCe framework

This repository demonstrates fast linear algebra on FPGA using the DaCe
parallel programming framework. The following program serves as a synthetic benchmark:

```
M1 = np.outer(x, y1) + A  // GER
M2 = np.outer(x, y2) + A  // GER
M3 = np.outer(x, y3) + A  // GER
M4 = np.outer(x, y4) + A  // GER
M5 = np.outer(x, y5) + A  // GER
M6 = np.outer(x, y6) + A  // GER
M7 = np.outer(x, y7) + A  // GER
M8 = np.outer(x, y8) + A  // GER

vector1 = M1 @ x  // GEMV
vector2 = M2 @ x  // GEMV
vector3 = M3 @ x  // GEMV
vector4 = M4 @ x  // GEMV
vector5 = M5 @ x  // GEMV
vector6 = M6 @ x  // GEMV
vector7 = M7 @ x  // GEMV
vector8 = M8 @ x  // GEMV

vector1 = vector1 + vector2  // AXPY
vector3 = vector3 + vector4  // AXPY
vector5 = vector5 + vector6  // AXPY
vector7 = vector7 + vector8  // AXPY

vector1 = vector1 + vector3  // AXPY
vector5 = vector5 + vector7  // AXPY

buf = vector1 + vector5  // AXPY
result = np.sum(buf)  // ASUM
```

Precompiled bitstreams for the FPGA are in `/bitstreams`

## Compile

To preprare for compilation run:

`source setSubmodules.sh`

to install and setup the DaCe framework and


`source setupPython.sh` (you must have the `virtualenv` package installed)

to setup
the Python environment. Run the below commands to compile, after compiling once one can ran
with the `-c` flag, which prevents recompilation and directly runs the previously compiled code.

### FPGA
Run: `performance_synthetic1.py -m hardware 8192`

### CPU
Make sure OpenBLAS is loaded in your environment
Run: `performance_synthetic1_cpu.py 8192`

### GPU
Make sure the CUDA toolkit is available in your environment
Run: `performance_synthetic1_gpu.py 8192`



## Run Benchmark

To run the benchmarks which will run the above scripts mutliple times and collect
the data and report median timings run the following commands.

### FPGA
Run `run_experiments_platforms_fpga.py -v xilinx`

### CPU
Run `run_experiments_platforms_cpu.py`

### GPU
Run `run_experiments_platforms_gpu.py`