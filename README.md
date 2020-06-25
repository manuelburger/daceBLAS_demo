# BLAS for FPGA based on the DaCe framework

This repository demonstrates fast linear algebra on FPGA using the DaCe
parallel programming framework

Precompiled bitstreams for the FPGA are in `/bitstreams`

## Compile

To preprare for compilation run:
`source setSubmodules.sh` to install and setup the DaCe framework
and
`source setupPython.sh` (you must have the `virtualenv` package installed) to setup
the Python environment

### FPGA
Run: `performance_synthetic1.py -m hardware 8192`

### CPU
Make sure OpenBLAS is loaded in your environment
Run: `performance_synthetic1_cpu.py 8192`

### GPU
Make sure the CUDA toolkit is available in your environment
Run: `performance_synthetic1_gpu.py 8192`

## Run Benchmark

### FPGA
Run `run_experiments_platforms_fpga.py -v xilinx`

### CPU
Run `run_experiments_platforms_cpu.py`

### GPU
Run `run_experiments_platforms_gpu.py`