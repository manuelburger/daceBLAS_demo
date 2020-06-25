#!/usr/bin/env python3
# coding: utf-8


import dace
from dace.memlet import Memlet
from dace import dtypes
import dace.libraries.blas as blas
import dace.libraries.blas.utility.memoryStreams as stream
import dace.libraries.blas.utility.memoryOperations as memOps
import dace.libraries.blas.utility.streaming as streaming
import numpy as np
import scipy
import time
import sys
import argparse


from dace.transformation import optimizer
# from dace.transformation.interstate import FPGATransformSDFG
from dace.libraries.blas.transformations.streamAccessTransform import *
from dace.libraries.blas.transformations.streamReadTransform import *
from dace.libraries.blas.transformations.streamWriteTransform import *
from dace.libraries.blas.transformations.streamFPGATransform import *
from dace.libraries.blas.transformations.globalMemoryAccessTransform import *


# ---------- ---------- ----------
# Read in command line arguments
# ---------- ---------- ----------
cmdParser = argparse.ArgumentParser()

cmdParser.add_argument("N", type=int)
cmdParser.add_argument("-p", "--platform", dest="platform", default="FPGA", help="Execution platform")
cmdParser.add_argument("-v", "--vendor", dest="vendor", default="xilinx", help="FPGA Vendor (xilinx, intel_fpga)")
cmdParser.add_argument("-m", "--mode", dest="mode", default="hardware", help="Execution Mode (hardware, simulation...)")
cmdParser.add_argument("-t", "--type", dest="type", default="single", help="Type precision: single or double")
cmdParser.add_argument("-c", "--cache", dest="cache", action='store_true')


args = cmdParser.parse_args()

testSize = args.N
platform = args.platform
vendor = args.vendor
mode = args.mode
precision = args.type
caching = args.cache

typeNumpy = np.float32
typeDace = dace.float32
if precision == "double":
    typeNumpy = np.float64
    typeDace = dace.float64


print("\n----- Input parsed -----")
print("Running on: ", vendor, " in ", platform, " in ", mode)
print("N = ", testSize, "type: ", precision, "\n")

# ---------- ---------- ----------
# Create testing SDFG
# ---------- ---------- ----------
VECWIDTH = 16
ROW_TILE = 8192
COL_TILE = 8192
PARTIAL_WIDTH = 16
DATATYPE = typeDace
DATATYPE_NP = typeNumpy

n = dace.symbol("n")
a = dace.symbol("a")

test_sdfg = dace.SDFG("perf_synthetic1")
test_state = test_sdfg.add_state("test_state")

test_sdfg.add_symbol(a.name, DATATYPE)

desc = test_sdfg.add_array('A_ger', shape=[n*n], dtype=DATATYPE)
desc[1].location = {'bank':0}
desc = test_sdfg.add_array('x_ger', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':1}

desc = test_sdfg.add_array('y1_ger', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':2}
desc = test_sdfg.add_array('y2_ger', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':2}
desc = test_sdfg.add_array('y3_ger', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':2}
desc = test_sdfg.add_array('y4_ger', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':2}
desc = test_sdfg.add_array('y5_ger', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':2}
desc = test_sdfg.add_array('y6_ger', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':2}
desc = test_sdfg.add_array('y7_ger', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':2}
desc = test_sdfg.add_array('y8_ger', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':2}

desc = test_sdfg.add_array('x_gemv', shape=[n], dtype=DATATYPE)
desc[1].location = {'bank':3}

desc = test_sdfg.add_array('res', shape=[1], dtype=DATATYPE)
desc[1].location = {'bank':0}

desc = test_sdfg.add_array('A1', shape=[n*n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('A2', shape=[n*n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('A3', shape=[n*n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('A4', shape=[n*n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('A5', shape=[n*n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('A6', shape=[n*n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('A7', shape=[n*n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('A8', shape=[n*n], dtype=DATATYPE, transient=True)


desc = test_sdfg.add_array('vec1', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('vec2', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('vec3', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('vec4', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('vec5', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('vec6', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('vec7', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('vec8', shape=[n], dtype=DATATYPE, transient=True)


desc = test_sdfg.add_array('buf1', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('buf2', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('buf3', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('buf4', shape=[n], dtype=DATATYPE, transient=True)

desc = test_sdfg.add_array('buf5', shape=[n], dtype=DATATYPE, transient=True)
desc = test_sdfg.add_array('buf6', shape=[n], dtype=DATATYPE, transient=True)

desc = test_sdfg.add_array('buf7', shape=[n], dtype=DATATYPE, transient=True)


# First layer GER
# ---------- ---------- ----------
ger1_node = blas.level2.ger.Ger(
    "GER1",
    dtype=DATATYPE,
    nTile = ROW_TILE,
    mTile = COL_TILE,
    n=n,
    m=n,
    a=a,
    vecWidthM=VECWIDTH
)
ger1_node.implementation = 'fpga_stream_tiledRows'

ger2_node = blas.level2.ger.Ger(
    "GER2",
    dtype=DATATYPE,
    nTile = ROW_TILE,
    mTile = COL_TILE,
    n=n,
    m=n,
    a=a,
    vecWidthM=VECWIDTH
)
ger2_node.implementation = 'fpga_stream_tiledRows'

ger3_node = blas.level2.ger.Ger(
    "GER3",
    dtype=DATATYPE,
    nTile = ROW_TILE,
    mTile = COL_TILE,
    n=n,
    m=n,
    a=a,
    vecWidthM=VECWIDTH
)
ger3_node.implementation = 'fpga_stream_tiledRows'

ger4_node = blas.level2.ger.Ger(
    "GER4",
    dtype=DATATYPE,
    nTile = ROW_TILE,
    mTile = COL_TILE,
    n=n,
    m=n,
    a=a,
    vecWidthM=VECWIDTH
)
ger4_node.implementation = 'fpga_stream_tiledRows'

ger5_node = blas.level2.ger.Ger(
    "GER5",
    dtype=DATATYPE,
    nTile = ROW_TILE,
    mTile = COL_TILE,
    n=n,
    m=n,
    a=a,
    vecWidthM=VECWIDTH
)
ger5_node.implementation = 'fpga_stream_tiledRows'

ger6_node = blas.level2.ger.Ger(
    "GER6",
    dtype=DATATYPE,
    nTile = ROW_TILE,
    mTile = COL_TILE,
    n=n,
    m=n,
    a=a,
    vecWidthM=VECWIDTH
)
ger6_node.implementation = 'fpga_stream_tiledRows'

ger7_node = blas.level2.ger.Ger(
    "GER7",
    dtype=DATATYPE,
    nTile = ROW_TILE,
    mTile = COL_TILE,
    n=n,
    m=n,
    a=a,
    vecWidthM=VECWIDTH
)
ger7_node.implementation = 'fpga_stream_tiledRows'

ger8_node = blas.level2.ger.Ger(
    "GER8",
    dtype=DATATYPE,
    nTile = ROW_TILE,
    mTile = COL_TILE,
    n=n,
    m=n,
    a=a,
    vecWidthM=VECWIDTH
)
ger8_node.implementation = 'fpga_stream_tiledRows'


A_in = test_state.add_read("A_ger")
x_in = test_state.add_read("x_ger")

y1 = test_state.add_read("y1_ger")
y2 = test_state.add_read("y2_ger")
y3 = test_state.add_read("y3_ger")
y4 = test_state.add_read("y4_ger")
y5 = test_state.add_read("y5_ger")
y6 = test_state.add_read("y6_ger")
y7 = test_state.add_read("y7_ger")
y8 = test_state.add_read("y8_ger")

A1 = test_state.add_access("A1")
A2 = test_state.add_access("A2")
A3 = test_state.add_access("A3")
A4 = test_state.add_access("A4")
A5 = test_state.add_access("A5")
A6 = test_state.add_access("A6")
A7 = test_state.add_access("A7")
A8 = test_state.add_access("A8")

test_state.add_memlet_path(
    A_in, ger1_node,
    dst_conn="_A",
    memlet=Memlet.simple(A_in.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A_in, ger2_node,
    dst_conn="_A",
    memlet=Memlet.simple(A_in.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A_in, ger3_node,
    dst_conn="_A",
    memlet=Memlet.simple(A_in.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A_in, ger4_node,
    dst_conn="_A",
    memlet=Memlet.simple(A_in.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A_in, ger5_node,
    dst_conn="_A",
    memlet=Memlet.simple(A_in.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A_in, ger6_node,
    dst_conn="_A",
    memlet=Memlet.simple(A_in.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A_in, ger7_node,
    dst_conn="_A",
    memlet=Memlet.simple(A_in.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A_in, ger8_node,
    dst_conn="_A",
    memlet=Memlet.simple(A_in.data, "0:n*n", veclen=VECWIDTH)
)





test_state.add_memlet_path(
    x_in, ger1_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_in.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_in, ger2_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_in.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_in, ger3_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_in.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_in, ger4_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_in.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_in, ger5_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_in.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_in, ger6_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_in.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_in, ger7_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_in.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_in, ger8_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_in.data, "0:n", veclen=VECWIDTH)
)



test_state.add_memlet_path(
    y1, ger1_node,
    dst_conn="_y",
    memlet=Memlet.simple(y1.data, "0:n")
)

test_state.add_memlet_path(
    y2, ger2_node,
    dst_conn="_y",
    memlet=Memlet.simple(y2.data, "0:n")
)

test_state.add_memlet_path(
    y3, ger3_node,
    dst_conn="_y",
    memlet=Memlet.simple(y3.data, "0:n")
)

test_state.add_memlet_path(
    y4, ger4_node,
    dst_conn="_y",
    memlet=Memlet.simple(y4.data, "0:n")
)

test_state.add_memlet_path(
    y5, ger5_node,
    dst_conn="_y",
    memlet=Memlet.simple(y5.data, "0:n")
)

test_state.add_memlet_path(
    y6, ger6_node,
    dst_conn="_y",
    memlet=Memlet.simple(y6.data, "0:n")
)

test_state.add_memlet_path(
    y7, ger7_node,
    dst_conn="_y",
    memlet=Memlet.simple(y7.data, "0:n")
)

test_state.add_memlet_path(
    y8, ger8_node,
    dst_conn="_y",
    memlet=Memlet.simple(y8.data, "0:n")
)

test_state.add_memlet_path(
    ger1_node, A1,
    src_conn="_RES",
    memlet=Memlet.simple(A1.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    ger2_node, A2,
    src_conn="_RES",
    memlet=Memlet.simple(A2.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    ger3_node, A3,
    src_conn="_RES",
    memlet=Memlet.simple(A3.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    ger4_node, A4,
    src_conn="_RES",
    memlet=Memlet.simple(A4.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    ger5_node, A5,
    src_conn="_RES",
    memlet=Memlet.simple(A5.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    ger6_node, A6,
    src_conn="_RES",
    memlet=Memlet.simple(A6.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    ger7_node, A7,
    src_conn="_RES",
    memlet=Memlet.simple(A7.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    ger8_node, A8,
    src_conn="_RES",
    memlet=Memlet.simple(A8.data, "0:n*n", veclen=VECWIDTH)
)






# Second layer GEMV
# ---------- ---------- ----------
gemv1_node = blas.level2.gemv.Gemv(
    "GEMV1",
    DATATYPE,
    nTile=ROW_TILE,
    mTile=COL_TILE,
    partialWidth = PARTIAL_WIDTH,
    n=n,
    m=n,
    a=a,
    b=0,
    vecWidthM=VECWIDTH
)
gemv1_node.implementation = 'fpga_stream_tiledRows'

gemv2_node = blas.level2.gemv.Gemv(
    "GEMV2",
    DATATYPE,
    nTile=ROW_TILE,
    mTile=COL_TILE,
    partialWidth = PARTIAL_WIDTH,
    n=n,
    m=n,
    a=a,
    b=0,
    vecWidthM=VECWIDTH
)
gemv2_node.implementation = 'fpga_stream_tiledRows'

gemv3_node = blas.level2.gemv.Gemv(
    "GEMV3",
    DATATYPE,
    nTile=ROW_TILE,
    mTile=COL_TILE,
    partialWidth = PARTIAL_WIDTH,
    n=n,
    m=n,
    a=a,
    b=0,
    vecWidthM=VECWIDTH
)
gemv3_node.implementation = 'fpga_stream_tiledRows'

gemv4_node = blas.level2.gemv.Gemv(
    "GEMV4",
    DATATYPE,
    nTile=ROW_TILE,
    mTile=COL_TILE,
    partialWidth = PARTIAL_WIDTH,
    n=n,
    m=n,
    a=a,
    b=0,
    vecWidthM=VECWIDTH
)
gemv4_node.implementation = 'fpga_stream_tiledRows'

gemv5_node = blas.level2.gemv.Gemv(
    "GEMV5",
    DATATYPE,
    nTile=ROW_TILE,
    mTile=COL_TILE,
    partialWidth = PARTIAL_WIDTH,
    n=n,
    m=n,
    a=a,
    b=0,
    vecWidthM=VECWIDTH
)
gemv5_node.implementation = 'fpga_stream_tiledRows'

gemv6_node = blas.level2.gemv.Gemv(
    "GEMV6",
    DATATYPE,
    nTile=ROW_TILE,
    mTile=COL_TILE,
    partialWidth = PARTIAL_WIDTH,
    n=n,
    m=n,
    a=a,
    b=0,
    vecWidthM=VECWIDTH
)
gemv6_node.implementation = 'fpga_stream_tiledRows'

gemv7_node = blas.level2.gemv.Gemv(
    "GEMV7",
    DATATYPE,
    nTile=ROW_TILE,
    mTile=COL_TILE,
    partialWidth = PARTIAL_WIDTH,
    n=n,
    m=n,
    a=a,
    b=0,
    vecWidthM=VECWIDTH
)
gemv7_node.implementation = 'fpga_stream_tiledRows'

gemv8_node = blas.level2.gemv.Gemv(
    "GEMV8",
    DATATYPE,
    nTile=ROW_TILE,
    mTile=COL_TILE,
    partialWidth = PARTIAL_WIDTH,
    n=n,
    m=n,
    a=a,
    b=0,
    vecWidthM=VECWIDTH
)
gemv8_node.implementation = 'fpga_stream_tiledRows'


x_gemv = test_state.add_read("x_gemv")

vec1 = test_state.add_access("vec1")
vec2 = test_state.add_access("vec2")
vec3 = test_state.add_access("vec3")
vec4 = test_state.add_access("vec4")
vec5 = test_state.add_access("vec5")
vec6 = test_state.add_access("vec6")
vec7 = test_state.add_access("vec7")
vec8 = test_state.add_access("vec8")

test_state.add_memlet_path(
    A1, gemv1_node,
    dst_conn="_A",
    memlet=Memlet.simple(A1.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A2, gemv2_node,
    dst_conn="_A",
    memlet=Memlet.simple(A2.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A3, gemv3_node,
    dst_conn="_A",
    memlet=Memlet.simple(A3.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A4, gemv4_node,
    dst_conn="_A",
    memlet=Memlet.simple(A4.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A5, gemv5_node,
    dst_conn="_A",
    memlet=Memlet.simple(A5.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A6, gemv6_node,
    dst_conn="_A",
    memlet=Memlet.simple(A6.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A7, gemv7_node,
    dst_conn="_A",
    memlet=Memlet.simple(A7.data, "0:n*n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    A8, gemv8_node,
    dst_conn="_A",
    memlet=Memlet.simple(A8.data, "0:n*n", veclen=VECWIDTH)
)



test_state.add_memlet_path(
    x_gemv, gemv1_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_gemv.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_gemv, gemv2_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_gemv.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_gemv, gemv3_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_gemv.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_gemv, gemv4_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_gemv.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_gemv, gemv5_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_gemv.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_gemv, gemv6_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_gemv.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_gemv, gemv7_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_gemv.data, "0:n", veclen=VECWIDTH)
)

test_state.add_memlet_path(
    x_gemv, gemv8_node,
    dst_conn="_x",
    memlet=Memlet.simple(x_gemv.data, "0:n", veclen=VECWIDTH)
)



test_state.add_memlet_path(
    gemv1_node, vec1,
    src_conn="_res",
    memlet=Memlet.simple(vec1.data, "0:n")
)

test_state.add_memlet_path(
    gemv2_node, vec2,
    src_conn="_res",
    memlet=Memlet.simple(vec2.data, "0:n")
)

test_state.add_memlet_path(
    gemv3_node, vec3,
    src_conn="_res",
    memlet=Memlet.simple(vec3.data, "0:n")
)

test_state.add_memlet_path(
    gemv4_node, vec4,
    src_conn="_res",
    memlet=Memlet.simple(vec4.data, "0:n")
)

test_state.add_memlet_path(
    gemv5_node, vec5,
    src_conn="_res",
    memlet=Memlet.simple(vec5.data, "0:n")
)

test_state.add_memlet_path(
    gemv6_node, vec6,
    src_conn="_res",
    memlet=Memlet.simple(vec6.data, "0:n")
)

test_state.add_memlet_path(
    gemv7_node, vec7,
    src_conn="_res",
    memlet=Memlet.simple(vec7.data, "0:n")
)

test_state.add_memlet_path(
    gemv8_node, vec8,
    src_conn="_res",
    memlet=Memlet.simple(vec8.data, "0:n")
)




# Third layer AXPY
# ---------- ---------- ----------
saxpy_node = blas.level1.axpy.Axpy("saxpy", DATATYPE , n=n, a=a)
saxpy_node.implementation = 'fpga_stream'

saxpy_node_l1_1 = blas.level1.axpy.Axpy("saxpy_l1_1", DATATYPE , n=n, a=a)
saxpy_node_l1_1.implementation = 'fpga_stream'

saxpy_node_l1_2 = blas.level1.axpy.Axpy("saxpy_l1_2", DATATYPE , n=n, a=a)
saxpy_node_l1_2.implementation = 'fpga_stream'

saxpy_node_l2_1 = blas.level1.axpy.Axpy("saxpy_l2_1", DATATYPE , n=n, a=a)
saxpy_node_l2_1.implementation = 'fpga_stream'

saxpy_node_l2_2 = blas.level1.axpy.Axpy("saxpy_l2_2", DATATYPE , n=n, a=a)
saxpy_node_l2_2.implementation = 'fpga_stream'

saxpy_node_l2_3 = blas.level1.axpy.Axpy("saxpy_l2_3", DATATYPE , n=n, a=a)
saxpy_node_l2_3.implementation = 'fpga_stream'

saxpy_node_l2_4 = blas.level1.axpy.Axpy("saxpy_l2_4", DATATYPE , n=n, a=a)
saxpy_node_l2_4.implementation = 'fpga_stream'

asum_node = blas.level1.asum.Asum(
    "blas_asum",
    dtype=typeDace,
    partialWidth=PARTIAL_WIDTH,
    n=n,
)
asum_node.implementation = 'fpga_stream_linear'


buf1 = test_state.add_access("buf1")
buf2 = test_state.add_access("buf2")
buf3 = test_state.add_access("buf3")
buf4 = test_state.add_access("buf4")
buf5 = test_state.add_access("buf5")
buf6 = test_state.add_access("buf6")
buf7 = test_state.add_access("buf7")

res = test_state.add_write("res")

# Connect first layer source
# ---------- ---------- ----------
test_state.add_memlet_path(
    vec1, saxpy_node_l2_1,
    dst_conn="_x",
    memlet=Memlet.simple(vec1.data, "0:n")
)

test_state.add_memlet_path(
    vec2, saxpy_node_l2_1,
    dst_conn="_y",
    memlet=Memlet.simple(vec2.data, "0:n")
)

test_state.add_memlet_path(
    vec3, saxpy_node_l2_2,
    dst_conn="_x",
    memlet=Memlet.simple(vec3.data, "0:n")
)

test_state.add_memlet_path(
    vec4, saxpy_node_l2_2,
    dst_conn="_y",
    memlet=Memlet.simple(vec4.data, "0:n")
)

test_state.add_memlet_path(
    vec5, saxpy_node_l2_3,
    dst_conn="_x",
    memlet=Memlet.simple(vec5.data, "0:n")
)

test_state.add_memlet_path(
    vec6, saxpy_node_l2_3,
    dst_conn="_y",
    memlet=Memlet.simple(vec6.data, "0:n")
)

test_state.add_memlet_path(
    vec7, saxpy_node_l2_4,
    dst_conn="_x",
    memlet=Memlet.simple(vec7.data, "0:n")
)

test_state.add_memlet_path(
    vec8, saxpy_node_l2_4,
    dst_conn="_y",
    memlet=Memlet.simple(vec8.data, "0:n")
)


# Connect second layer source
# ---------- ---------- ----------
test_state.add_memlet_path(
    saxpy_node_l2_1, buf1,
    src_conn='_res',
    memlet=Memlet.simple(buf1.data, "0:n")
)

test_state.add_memlet_path(
    buf1, saxpy_node_l1_1,
    dst_conn='_x',
    memlet=Memlet.simple(buf1.data, "0:n")
)

test_state.add_memlet_path(
    saxpy_node_l2_2, buf2,
    src_conn='_res',
    memlet=Memlet.simple(buf2.data, "0:n")
)

test_state.add_memlet_path(
    buf2, saxpy_node_l1_1,
    dst_conn='_y',
    memlet=Memlet.simple(buf2.data, "0:n")
)


test_state.add_memlet_path(
    saxpy_node_l2_3, buf3,
    src_conn='_res',
    memlet=Memlet.simple(buf3.data, "0:n")
)

test_state.add_memlet_path(
    buf3, saxpy_node_l1_2,
    dst_conn='_x',
    memlet=Memlet.simple(buf3.data, "0:n")
)

test_state.add_memlet_path(
    saxpy_node_l2_4, buf4,
    src_conn='_res',
    memlet=Memlet.simple(buf4.data, "0:n")
)

test_state.add_memlet_path(
    buf4, saxpy_node_l1_2,
    dst_conn='_y',
    memlet=Memlet.simple(buf4.data, "0:n")
)


# Connect last layer axpy
# ---------- ---------- ----------
test_state.add_memlet_path(
    saxpy_node_l1_1, buf5,
    src_conn='_res',
    memlet=Memlet.simple(buf5.data, "0:n")
)

test_state.add_memlet_path(
    buf5, saxpy_node,
    dst_conn='_x',
    memlet=Memlet.simple(buf5.data, "0:n")
)

test_state.add_memlet_path(
    saxpy_node_l1_2, buf6,
    src_conn='_res',
    memlet=Memlet.simple(buf6.data, "0:n")
)

test_state.add_memlet_path(
    buf6, saxpy_node,
    dst_conn='_y',
    memlet=Memlet.simple(buf6.data, "0:n")
)


# Connect result
# ---------- ---------- ----------
test_state.add_memlet_path(
    saxpy_node, buf7,
    src_conn='_res',
    memlet=Memlet.simple(buf7.data, "0:n")
)


test_state.add_memlet_path(
    buf7, asum_node,
    dst_conn='_x',
    memlet=Memlet.simple(buf7.data, "0:n")
)

test_state.add_memlet_path(
    asum_node, res,
    src_conn='_res',
    memlet=Memlet.simple(res.data, "0")
)








# ---------- ---------- ----------
# TRANSFORM
# ---------- ---------- ----------
test_sdfg.validate()

test_sdfg.apply_transformations(streamFPGATransform)

# # ger -> gemv
test_sdfg.apply_transformations(streamAccess)
test_sdfg.apply_transformations(streamAccess)
test_sdfg.apply_transformations(streamAccess)
test_sdfg.apply_transformations(streamAccess)

# # gemv -> axpy
# test_sdfg.apply_transformations(streamAccess)
# test_sdfg.apply_transformations(streamAccess)
# test_sdfg.apply_transformations(streamAccess)
# test_sdfg.apply_transformations(streamAccess)

# # axpy -> axpy
# test_sdfg.apply_transformations(streamAccess)
# test_sdfg.apply_transformations(streamAccess)

# # axpy -> asum
# test_sdfg.apply_transformations(streamAccess)

# # A, x : ger
test_sdfg.apply_transformations(streamRead)
test_sdfg.apply_transformations(streamRead)

# y : ger
test_sdfg.apply_transformations(streamRead)
test_sdfg.apply_transformations(streamRead)
test_sdfg.apply_transformations(streamRead)
test_sdfg.apply_transformations(streamRead)
test_sdfg.apply_transformations(streamRead)
test_sdfg.apply_transformations(streamRead)
test_sdfg.apply_transformations(streamRead)
test_sdfg.apply_transformations(streamRead)

# x : gemv
test_sdfg.apply_transformations(streamRead)

# result
test_sdfg.apply_transformations(streamWrite)



test_sdfg.expand_library_nodes()

# ---------- ---------- ----------
# Setup measurments
# ---------- ---------- ----------

# Remove extraneous states
# ---------- ---------- ----------
# test_sdfg.apply_strict_transformations()

# ---------- ---------- ----------
# Create an SDFG optimizer
# ---------- ---------- ----------   
dace.config.Config.set("compiler", "fpga_vendor", value=vendor)
dace.config.Config.set("compiler", vendor, "mode", value=mode)

test_sdfg.validate()
if caching:
    dace.config.Config.set("compiler", "use_cache", value="true")
    
compiledSDFG = test_sdfg.compile(optimizer=False)

# ---------- ---------- ----------
# Test function
# ---------- ---------- ----------
np.random.seed(123)
upperBound = 5
# A_ger = np.random.randint(upperBound, size=testSize*testSize).astype(DATATYPE_NP)
# x_ger = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
# y_ger = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
# x_gemv = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
# y_axpy = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)

# A_ger = np.ones(testSize*testSize).astype(DATATYPE_NP)
A_ger = np.random.randint(upperBound, size=testSize*testSize).astype(DATATYPE_NP)
A_ger_copy = A_ger.copy().reshape(testSize, testSize)

x_ger_data  = np.ones(testSize).astype(DATATYPE_NP)

# y1_ger_data = np.ones(testSize).astype(DATATYPE_NP)
# y2_ger_data  = np.ones(testSize).astype(DATATYPE_NP)
# y3_ger_data  = np.ones(testSize).astype(DATATYPE_NP)
# y4_ger_data  = np.ones(testSize).astype(DATATYPE_NP)
# y5_ger_data = np.ones(testSize).astype(DATATYPE_NP)
# y6_ger_data  = np.ones(testSize).astype(DATATYPE_NP)
# y7_ger_data  = np.ones(testSize).astype(DATATYPE_NP)
# y8_ger_data  = np.ones(testSize).astype(DATATYPE_NP)

y1_ger_data = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
y2_ger_data  = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
y3_ger_data  = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
y4_ger_data  = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
y5_ger_data = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
y6_ger_data  = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
y7_ger_data  = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)
y8_ger_data  = np.random.randint(upperBound, size=testSize).astype(DATATYPE_NP)

x_gemv = np.ones(testSize).astype(DATATYPE_NP)

y_axpy = np.ones(testSize).astype(DATATYPE_NP)

c = np.zeros(1).astype(DATATYPE_NP)
scaling = np.array([1.0], DATATYPE_NP)


print("\n----- COMPILE & RUN (FPGA) -----")
start = time.time()

compiledSDFG(
    A_ger=A_ger,
    x_ger=x_ger_data,
    y1_ger=y1_ger_data,
    y2_ger=y2_ger_data,
    y3_ger=y3_ger_data,
    y4_ger=y4_ger_data,
    y5_ger=y5_ger_data,
    y6_ger=y6_ger_data,
    y7_ger=y7_ger_data,
    y8_ger=y8_ger_data,
    x_gemv=x_gemv,
    res=c,
    a=scaling[0],
    n=np.int32(testSize)
)

end = time.time()
runtime = (end - start)
print("Runtime:", runtime)

print("\n----- VERIFICATION (CPU) -----")
start = time.time()

M1 = np.outer(x_ger_data, y1_ger_data) + A_ger_copy
M2 = np.outer(x_ger_data, y2_ger_data) + A_ger_copy
M3 = np.outer(x_ger_data, y3_ger_data) + A_ger_copy
M4 = np.outer(x_ger_data, y4_ger_data) + A_ger_copy
M5 = np.outer(x_ger_data, y5_ger_data) + A_ger_copy
M6 = np.outer(x_ger_data, y6_ger_data) + A_ger_copy
M7 = np.outer(x_ger_data, y7_ger_data) + A_ger_copy
M8 = np.outer(x_ger_data, y8_ger_data) + A_ger_copy

vector1 = M1 @ x_gemv
vector2 = M2 @ x_gemv
vector3 = M3 @ x_gemv
vector4 = M4 @ x_gemv
vector5 = M5 @ x_gemv
vector6 = M6 @ x_gemv
vector7 = M7 @ x_gemv
vector8 = M8 @ x_gemv

vector1 = vector1 + vector2
vector3 = vector3 + vector4
vector5 = vector5 + vector6
vector7 = vector7 + vector8

vector1 = vector1 + vector3
vector5 = vector5 + vector7

ref_result = vector1 + vector5
ref_result = np.sum(ref_result)

end = time.time()
print("Verification time: ", end - start)

print("Res:", c[0])
print("Ref:", ref_result)

passed = abs(c[0] - ref_result) / ref_result < 0.001

print("Passed Test: ", passed)

        




