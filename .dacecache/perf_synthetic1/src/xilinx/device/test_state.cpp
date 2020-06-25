#include <dace/xilinx/device.h>
#include <dace/math.h>
#include <dace/complex.h>

void module_saxpy_l1_1(dace::FIFO<float, 1, 32> &_res_to_saxpy_l1_1_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l1_1_y_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_x_0, float a, int n) {
    {
        auto ___y = dace::make_streamview(_res_to_saxpy_l1_1_y_0);
        auto &_y = ___y;
        auto ___x = dace::make_streamview(_res_to_saxpy_l1_1_x_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_x_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_vecAdd_graph_5_state_0:
            {
                {
                    for (int i = 0; i < n; i += 1) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS LOOP_FLATTEN
                        {
                            auto __x_con = _x;
                            auto x_con = __x_con.pop();
                            auto __y_con = _y;
                            auto y_con = __y_con.pop();

                            auto __z_con = _res;
                            dace::vec<float, 1> z_con;

                            ////////////////////
                            // Tasklet code (vecAdd_task)
                            z_con = ((a * x_con) + y_con);
                            ////////////////////

                            __z_con.write(z_con);
                        }
                    }
                }
            }
            __state_exit_vecAdd_graph_5_sdfg:;
        }    ///////////////////

    }
}

void module_saxpy_l2_2(dace::FIFO<float, 1, 32> &_res_to_saxpy_l1_1_y_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_2_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_2_y_0, float a, int n) {
    {
        auto ___y = dace::make_streamview(_res_to_saxpy_l2_2_y_0);
        auto &_y = ___y;
        auto ___x = dace::make_streamview(_res_to_saxpy_l2_2_x_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l1_1_y_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_vecAdd_graph_2_state_0:
            {
                {
                    for (int i = 0; i < n; i += 1) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS LOOP_FLATTEN
                        {
                            auto __x_con = _x;
                            auto x_con = __x_con.pop();
                            auto __y_con = _y;
                            auto y_con = __y_con.pop();

                            auto __z_con = _res;
                            dace::vec<float, 1> z_con;

                            ////////////////////
                            // Tasklet code (vecAdd_task)
                            z_con = ((a * x_con) + y_con);
                            ////////////////////

                            __z_con.write(z_con);
                        }
                    }
                }
            }
            __state_exit_vecAdd_graph_2_sdfg:;
        }    ///////////////////

    }
}

void module_GEMV8(dace::FIFO<float, 16, 32> &_RES_to_GEMV8_A_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_4_y_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV8_0, float a, int n) {
    {
        auto ___A = dace::make_streamview(_RES_to_GEMV8_A_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_gemv_GEMV8_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l2_4_y_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_gemv_fpga_stream_rowTiles_state_0:
            {
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            auto ___A_yTile = _A;
                            auto &_A_yTile = ___A_yTile;
                            auto ___x_yTile = _x;
                            auto &_x_yTile = ___x_yTile;
                            auto __yTile = _res;
                            auto &yTile = __yTile;

                            {    ///////////////////
                                int __dacesym_a = a;
                                int __dacesym_n = n;
                                auto a = __dacesym_a;
                                auto n = __dacesym_n;
                                dace::vec<float, 1> y_tileRes[8192];

                                __state_yTile_sdfg_yTile_init:
                                {
                                    {
                                        for (int j_init = 0; j_init < 8192; j_init += 1) {
                                            #pragma HLS UNROLL
                                            {

                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (y_tileRes + j_init);
                                                dace::vec<float, 1> out;

                                                ////////////////////
                                                // Tasklet code (init_y_tileRes)
                                                out = 0;
                                                ////////////////////

                                                __out.write(out);
                                                #pragma HLS DEPENDENCE variable=out false
                                            }
                                        }
                                    }
                                }
                                __state_yTile_sdfg_yTile_compute:
                                {
                                    {
                                        for (long long j = 0; j < (n / 8192); j += 1) {
                                            {
                                                for (int ii = 0; ii < 8192; ii += 1) {
                                                    {
                                                        auto ___A_red = _A_yTile;
                                                        auto &_A_red = ___A_red;
                                                        auto ___x_red = _x_yTile;
                                                        auto &_x_red = ___x_red;
                                                        auto ___y_red = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_tileRes, 1);
                                                        auto *_y_red = ___y_red.ptr<1>();
                                                        auto ___res_red = yTile;
                                                        auto &_res_red = ___res_red;

                                                        {    ///////////////////
                                                            int __dacesym_a = a;
                                                            int __dacesym_ii = ii;
                                                            int __dacesym_j = j;
                                                            int __dacesym_n = n;
                                                            auto a = __dacesym_a;
                                                            auto ii = __dacesym_ii;
                                                            auto j = __dacesym_j;
                                                            auto n = __dacesym_n;
                                                            dace::vec<float, 1> red_buf[16];
                                                            dace::vec<float, 1> res_buf[1];
                                                            #pragma HLS ARRAY_PARTITION variable=res_buf complete

                                                            __state_redTile_sdfg_init_reduceTile:
                                                            {
                                                                {
                                                                    for (int j_init = 0; j_init < 16; j_init += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (red_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_red_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                                {
                                                                    {
                                                                        const int j_init = 0; // Degenerate loop
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (res_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_res_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if ((j == 0)) {
                                                                __state_redTile_sdfg_read_y_reduceTile:
                                                                {
                                                                    {

                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                        dace::vec<float, 1> outCon;

                                                                        ////////////////////
                                                                        // Tasklet code (read_y_tasklet)
                                                                        outCon = 0;
                                                                        ////////////////////

                                                                        __outCon.write(outCon);
                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                    }
                                                                }
                                                                __state_exit_redTile_sdfg_init_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_read_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_init_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_compute_reduceTile:
                                                            {
                                                                dace::vec<float, 16> x_buf[(8192 / 16)];
                                                                {
                                                                    for (int jj = 0; jj < 512; jj += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto ___A_unroll = _A_red;
                                                                            auto &_A_unroll = ___A_unroll;
                                                                            auto ___x_unroll = _x_red;
                                                                            auto &_x_unroll = ___x_unroll;
                                                                            auto ___buf_in_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *_buf_in_unroll = ___buf_in_unroll.ptr<1>();
                                                                            auto __buf_out = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *buf_out = __buf_out.ptr<1>();
                                                                            auto ___x_buf = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                            auto *_x_buf = ___x_buf.ptr<16>();

                                                                            {    ///////////////////
                                                                                int __dacesym_a = a;
                                                                                int __dacesym_ii = ii;
                                                                                int __dacesym_jj = jj;
                                                                                auto a = __dacesym_a;
                                                                                auto ii = __dacesym_ii;
                                                                                auto jj = __dacesym_jj;
                                                                                dace::vec<float, 1> buf_reg[1];
                                                                                #pragma HLS ARRAY_PARTITION variable=buf_reg complete
                                                                                dace::vec<float, 1> memBuf_A[16];
                                                                                #pragma HLS ARRAY_PARTITION variable=memBuf_A complete

                                                                                __state_partial_reduction_inner_8_init_state:
                                                                                {
                                                                                    dace::vec<float, 1> vecBuf_A[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=vecBuf_A complete
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(_A_unroll.pop()), vecBuf_A);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_A false
                                                                                    {
                                                                                        for (int k_stream = 0; k_stream < 16; k_stream += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (vecBuf_A + k_stream);
                                                                                                dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (memBuf_A + k_stream);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (streamToLocalA_map)
                                                                                                outCon = inCon;
                                                                                                ////////////////////

                                                                                                __outCon.write(outCon);
                                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    {
                                                                                        {
                                                                                            const int j_init = 0; // Degenerate loop
                                                                                            {

                                                                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg + j_init);
                                                                                                dace::vec<float, 1> out;

                                                                                                ////////////////////
                                                                                                // Tasklet code (init_buf_reg)
                                                                                                out = 0;
                                                                                                ////////////////////

                                                                                                __out.write(out);
                                                                                                #pragma HLS DEPENDENCE variable=out false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                if ((ii == 0)) {
                                                                                    __state_partial_reduction_inner_8_readX_state:
                                                                                    {
                                                                                        {
                                                                                            auto __inCon = _x_unroll;
                                                                                            auto inCon = __inCon.pop();

                                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf + jj);
                                                                                            dace::vec<float, 16> outCon;

                                                                                            ////////////////////
                                                                                            // Tasklet code (streamToLocal_map)
                                                                                            outCon = inCon;
                                                                                            ////////////////////

                                                                                            __outCon.write(outCon);
                                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                                        }
                                                                                    }
                                                                                    __state_exit_partial_reduction_inner_8_init_state_then:;
                                                                                    } else {
                                                                                    __state_partial_reduction_inner_8_readEmpty_state:
                                                                                    ;
                                                                                    __state_exit_partial_reduction_inner_8_init_state_else:;
                                                                                }
                                                                                __state_partial_reduction_inner_8_compute_state:
                                                                                {
                                                                                    dace::vec<float, 16> vecBuf_x;
                                                                                    dace::vec<float, 1> memBuf_x[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=memBuf_x complete
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf + jj);
                                                                                        dace::vec<float, 16> inCon = __inCon.val<16>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&vecBuf_x);
                                                                                        dace::vec<float, 16> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (streamToLocal_map)
                                                                                        outCon = inCon;
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(vecBuf_x), memBuf_x);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_x false
                                                                                    #pragma HLS DEPENDENCE variable=memBuf_x false
                                                                                    {
                                                                                        for (int j_inner = 0; j_inner < 16; j_inner += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __A_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_A + j_inner);
                                                                                                dace::vec<float, 1> A_con = __A_con.val<1>();
                                                                                                auto __x_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_x + j_inner);
                                                                                                dace::vec<float, 1> x_con = __x_con.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (compute_task)
                                                                                                outCon = ((a * A_con) * x_con);
                                                                                                ////////////////////

                                                                                                __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                __state_partial_reduction_inner_8_write_state:
                                                                                {
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (buf_reg);
                                                                                        dace::vec<float, 1> inCon = __inCon.val<1>();
                                                                                        auto __prevCon = dace::ArrayViewIn<float, 0, 1, 1> (_buf_in_unroll + (jj % 16));
                                                                                        dace::vec<float, 1> prevCon = __prevCon.val<1>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_out + (jj % 16));
                                                                                        dace::vec<float, 1> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (write_out_task)
                                                                                        outCon = (prevCon + inCon);
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                }
                                                                                __state_exit_partial_reduction_inner_8_sdfg:;
                                                                            }    ///////////////////

                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_red_reduceTile:
                                                            {
                                                                {
                                                                    for (int k = 0; k < 16; k += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (red_buf + k);
                                                                            dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (res_buf);
                                                                            dace::vec<float, 1> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (finalReduction)
                                                                            outCon = inCon;
                                                                            ////////////////////

                                                                            __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_store_reduceTile:
                                                            {
                                                                {
                                                                    auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (res_buf);
                                                                    dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                    auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                    dace::vec<float, 1> outCon;

                                                                    ////////////////////
                                                                    // Tasklet code (storeRed_task)
                                                                    outCon = inCon;
                                                                    ////////////////////

                                                                    __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                }
                                                            }
                                                            if ((j == ((n / 8192) - 1))) {
                                                                __state_redTile_sdfg_write_y_reduceTile:
                                                                {
                                                                    _res_red.push(dace::Read<float, 1>(_y_red + ii));
                                                                    #pragma HLS DEPENDENCE variable=_y_red false
                                                                }
                                                                __state_exit_redTile_sdfg_store_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_write_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_store_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_end_reduceTile:
                                                            ;
                                                            __state_exit_redTile_sdfg_sdfg:;
                                                        }    ///////////////////

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                __state_exit_yTile_sdfg_sdfg:;
                            }    ///////////////////

                        }
                    }
                }
            }
            __state_exit_gemv_fpga_stream_rowTiles_sdfg:;
        }    ///////////////////

    }
}

void module_GEMV4(dace::FIFO<float, 16, 32> &_RES_to_GEMV4_A_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_2_y_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV4_0, float a, int n) {
    {
        auto ___A = dace::make_streamview(_RES_to_GEMV4_A_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_gemv_GEMV4_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l2_2_y_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_gemv_fpga_stream_rowTiles_4_state_0:
            {
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            auto ___A_yTile = _A;
                            auto &_A_yTile = ___A_yTile;
                            auto ___x_yTile = _x;
                            auto &_x_yTile = ___x_yTile;
                            auto __yTile = _res;
                            auto &yTile = __yTile;

                            {    ///////////////////
                                int __dacesym_a = a;
                                int __dacesym_n = n;
                                auto a = __dacesym_a;
                                auto n = __dacesym_n;
                                dace::vec<float, 1> y_tileRes[8192];

                                __state_yTile_sdfg_4_yTile_init:
                                {
                                    {
                                        for (int j_init = 0; j_init < 8192; j_init += 1) {
                                            #pragma HLS UNROLL
                                            {

                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (y_tileRes + j_init);
                                                dace::vec<float, 1> out;

                                                ////////////////////
                                                // Tasklet code (init_y_tileRes)
                                                out = 0;
                                                ////////////////////

                                                __out.write(out);
                                                #pragma HLS DEPENDENCE variable=out false
                                            }
                                        }
                                    }
                                }
                                __state_yTile_sdfg_4_yTile_compute:
                                {
                                    {
                                        for (long long j = 0; j < (n / 8192); j += 1) {
                                            {
                                                for (int ii = 0; ii < 8192; ii += 1) {
                                                    {
                                                        auto ___A_red = _A_yTile;
                                                        auto &_A_red = ___A_red;
                                                        auto ___x_red = _x_yTile;
                                                        auto &_x_red = ___x_red;
                                                        auto ___y_red = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_tileRes, 1);
                                                        auto *_y_red = ___y_red.ptr<1>();
                                                        auto ___res_red = yTile;
                                                        auto &_res_red = ___res_red;

                                                        {    ///////////////////
                                                            int __dacesym_a = a;
                                                            int __dacesym_ii = ii;
                                                            int __dacesym_j = j;
                                                            int __dacesym_n = n;
                                                            auto a = __dacesym_a;
                                                            auto ii = __dacesym_ii;
                                                            auto j = __dacesym_j;
                                                            auto n = __dacesym_n;
                                                            dace::vec<float, 1> red_buf[16];
                                                            dace::vec<float, 1> res_buf[1];
                                                            #pragma HLS ARRAY_PARTITION variable=res_buf complete

                                                            __state_redTile_sdfg_4_init_reduceTile:
                                                            {
                                                                {
                                                                    for (int j_init = 0; j_init < 16; j_init += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (red_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_red_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                                {
                                                                    {
                                                                        const int j_init = 0; // Degenerate loop
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (res_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_res_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if ((j == 0)) {
                                                                __state_redTile_sdfg_4_read_y_reduceTile:
                                                                {
                                                                    {

                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                        dace::vec<float, 1> outCon;

                                                                        ////////////////////
                                                                        // Tasklet code (read_y_tasklet)
                                                                        outCon = 0;
                                                                        ////////////////////

                                                                        __outCon.write(outCon);
                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                    }
                                                                }
                                                                __state_exit_redTile_sdfg_4_init_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_4_read_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_4_init_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_4_compute_reduceTile:
                                                            {
                                                                dace::vec<float, 16> x_buf[(8192 / 16)];
                                                                {
                                                                    for (int jj = 0; jj < 512; jj += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto ___A_unroll = _A_red;
                                                                            auto &_A_unroll = ___A_unroll;
                                                                            auto ___x_unroll = _x_red;
                                                                            auto &_x_unroll = ___x_unroll;
                                                                            auto ___buf_in_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *_buf_in_unroll = ___buf_in_unroll.ptr<1>();
                                                                            auto __buf_out = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *buf_out = __buf_out.ptr<1>();
                                                                            auto ___x_buf = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                            auto *_x_buf = ___x_buf.ptr<16>();

                                                                            {    ///////////////////
                                                                                int __dacesym_a = a;
                                                                                int __dacesym_ii = ii;
                                                                                int __dacesym_jj = jj;
                                                                                auto a = __dacesym_a;
                                                                                auto ii = __dacesym_ii;
                                                                                auto jj = __dacesym_jj;
                                                                                dace::vec<float, 1> buf_reg[1];
                                                                                #pragma HLS ARRAY_PARTITION variable=buf_reg complete
                                                                                dace::vec<float, 1> memBuf_A[16];
                                                                                #pragma HLS ARRAY_PARTITION variable=memBuf_A complete

                                                                                __state_partial_reduction_inner_4_init_state:
                                                                                {
                                                                                    dace::vec<float, 1> vecBuf_A[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=vecBuf_A complete
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(_A_unroll.pop()), vecBuf_A);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_A false
                                                                                    {
                                                                                        for (int k_stream = 0; k_stream < 16; k_stream += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (vecBuf_A + k_stream);
                                                                                                dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (memBuf_A + k_stream);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (streamToLocalA_map)
                                                                                                outCon = inCon;
                                                                                                ////////////////////

                                                                                                __outCon.write(outCon);
                                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    {
                                                                                        {
                                                                                            const int j_init = 0; // Degenerate loop
                                                                                            {

                                                                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg + j_init);
                                                                                                dace::vec<float, 1> out;

                                                                                                ////////////////////
                                                                                                // Tasklet code (init_buf_reg)
                                                                                                out = 0;
                                                                                                ////////////////////

                                                                                                __out.write(out);
                                                                                                #pragma HLS DEPENDENCE variable=out false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                if ((ii == 0)) {
                                                                                    __state_partial_reduction_inner_4_readX_state:
                                                                                    {
                                                                                        {
                                                                                            auto __inCon = _x_unroll;
                                                                                            auto inCon = __inCon.pop();

                                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf + jj);
                                                                                            dace::vec<float, 16> outCon;

                                                                                            ////////////////////
                                                                                            // Tasklet code (streamToLocal_map)
                                                                                            outCon = inCon;
                                                                                            ////////////////////

                                                                                            __outCon.write(outCon);
                                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                                        }
                                                                                    }
                                                                                    __state_exit_partial_reduction_inner_4_init_state_then:;
                                                                                    } else {
                                                                                    __state_partial_reduction_inner_4_readEmpty_state:
                                                                                    ;
                                                                                    __state_exit_partial_reduction_inner_4_init_state_else:;
                                                                                }
                                                                                __state_partial_reduction_inner_4_compute_state:
                                                                                {
                                                                                    dace::vec<float, 16> vecBuf_x;
                                                                                    dace::vec<float, 1> memBuf_x[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=memBuf_x complete
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf + jj);
                                                                                        dace::vec<float, 16> inCon = __inCon.val<16>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&vecBuf_x);
                                                                                        dace::vec<float, 16> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (streamToLocal_map)
                                                                                        outCon = inCon;
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(vecBuf_x), memBuf_x);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_x false
                                                                                    #pragma HLS DEPENDENCE variable=memBuf_x false
                                                                                    {
                                                                                        for (int j_inner = 0; j_inner < 16; j_inner += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __A_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_A + j_inner);
                                                                                                dace::vec<float, 1> A_con = __A_con.val<1>();
                                                                                                auto __x_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_x + j_inner);
                                                                                                dace::vec<float, 1> x_con = __x_con.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (compute_task)
                                                                                                outCon = ((a * A_con) * x_con);
                                                                                                ////////////////////

                                                                                                __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                __state_partial_reduction_inner_4_write_state:
                                                                                {
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (buf_reg);
                                                                                        dace::vec<float, 1> inCon = __inCon.val<1>();
                                                                                        auto __prevCon = dace::ArrayViewIn<float, 0, 1, 1> (_buf_in_unroll + (jj % 16));
                                                                                        dace::vec<float, 1> prevCon = __prevCon.val<1>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_out + (jj % 16));
                                                                                        dace::vec<float, 1> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (write_out_task)
                                                                                        outCon = (prevCon + inCon);
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                }
                                                                                __state_exit_partial_reduction_inner_4_sdfg:;
                                                                            }    ///////////////////

                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_4_red_reduceTile:
                                                            {
                                                                {
                                                                    for (int k = 0; k < 16; k += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (red_buf + k);
                                                                            dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (res_buf);
                                                                            dace::vec<float, 1> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (finalReduction)
                                                                            outCon = inCon;
                                                                            ////////////////////

                                                                            __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_4_store_reduceTile:
                                                            {
                                                                {
                                                                    auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (res_buf);
                                                                    dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                    auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                    dace::vec<float, 1> outCon;

                                                                    ////////////////////
                                                                    // Tasklet code (storeRed_task)
                                                                    outCon = inCon;
                                                                    ////////////////////

                                                                    __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                }
                                                            }
                                                            if ((j == ((n / 8192) - 1))) {
                                                                __state_redTile_sdfg_4_write_y_reduceTile:
                                                                {
                                                                    _res_red.push(dace::Read<float, 1>(_y_red + ii));
                                                                    #pragma HLS DEPENDENCE variable=_y_red false
                                                                }
                                                                __state_exit_redTile_sdfg_4_store_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_4_write_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_4_store_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_4_end_reduceTile:
                                                            ;
                                                            __state_exit_redTile_sdfg_4_sdfg:;
                                                        }    ///////////////////

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                __state_exit_yTile_sdfg_4_sdfg:;
                            }    ///////////////////

                        }
                    }
                }
            }
            __state_exit_gemv_fpga_stream_rowTiles_4_sdfg:;
        }    ///////////////////

    }
}

void module_GEMV1(dace::FIFO<float, 16, 32> &_RES_to_GEMV1_A_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_1_x_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV1_0, float a, int n) {
    {
        auto ___A = dace::make_streamview(_RES_to_GEMV1_A_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_gemv_GEMV1_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l2_1_x_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_gemv_fpga_stream_rowTiles_1_state_0:
            {
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            auto ___A_yTile = _A;
                            auto &_A_yTile = ___A_yTile;
                            auto ___x_yTile = _x;
                            auto &_x_yTile = ___x_yTile;
                            auto __yTile = _res;
                            auto &yTile = __yTile;

                            {    ///////////////////
                                int __dacesym_a = a;
                                int __dacesym_n = n;
                                auto a = __dacesym_a;
                                auto n = __dacesym_n;
                                dace::vec<float, 1> y_tileRes[8192];

                                __state_yTile_sdfg_1_yTile_init:
                                {
                                    {
                                        for (int j_init = 0; j_init < 8192; j_init += 1) {
                                            #pragma HLS UNROLL
                                            {

                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (y_tileRes + j_init);
                                                dace::vec<float, 1> out;

                                                ////////////////////
                                                // Tasklet code (init_y_tileRes)
                                                out = 0;
                                                ////////////////////

                                                __out.write(out);
                                                #pragma HLS DEPENDENCE variable=out false
                                            }
                                        }
                                    }
                                }
                                __state_yTile_sdfg_1_yTile_compute:
                                {
                                    {
                                        for (long long j = 0; j < (n / 8192); j += 1) {
                                            {
                                                for (int ii = 0; ii < 8192; ii += 1) {
                                                    {
                                                        auto ___A_red = _A_yTile;
                                                        auto &_A_red = ___A_red;
                                                        auto ___x_red = _x_yTile;
                                                        auto &_x_red = ___x_red;
                                                        auto ___y_red = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_tileRes, 1);
                                                        auto *_y_red = ___y_red.ptr<1>();
                                                        auto ___res_red = yTile;
                                                        auto &_res_red = ___res_red;

                                                        {    ///////////////////
                                                            int __dacesym_a = a;
                                                            int __dacesym_ii = ii;
                                                            int __dacesym_j = j;
                                                            int __dacesym_n = n;
                                                            auto a = __dacesym_a;
                                                            auto ii = __dacesym_ii;
                                                            auto j = __dacesym_j;
                                                            auto n = __dacesym_n;
                                                            dace::vec<float, 1> red_buf[16];
                                                            dace::vec<float, 1> res_buf[1];
                                                            #pragma HLS ARRAY_PARTITION variable=res_buf complete

                                                            __state_redTile_sdfg_1_init_reduceTile:
                                                            {
                                                                {
                                                                    for (int j_init = 0; j_init < 16; j_init += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (red_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_red_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                                {
                                                                    {
                                                                        const int j_init = 0; // Degenerate loop
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (res_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_res_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if ((j == 0)) {
                                                                __state_redTile_sdfg_1_read_y_reduceTile:
                                                                {
                                                                    {

                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                        dace::vec<float, 1> outCon;

                                                                        ////////////////////
                                                                        // Tasklet code (read_y_tasklet)
                                                                        outCon = 0;
                                                                        ////////////////////

                                                                        __outCon.write(outCon);
                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                    }
                                                                }
                                                                __state_exit_redTile_sdfg_1_init_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_1_read_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_1_init_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_1_compute_reduceTile:
                                                            {
                                                                dace::vec<float, 16> x_buf[(8192 / 16)];
                                                                {
                                                                    for (int jj = 0; jj < 512; jj += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto ___A_unroll = _A_red;
                                                                            auto &_A_unroll = ___A_unroll;
                                                                            auto ___x_unroll = _x_red;
                                                                            auto &_x_unroll = ___x_unroll;
                                                                            auto ___buf_in_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *_buf_in_unroll = ___buf_in_unroll.ptr<1>();
                                                                            auto __buf_out = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *buf_out = __buf_out.ptr<1>();
                                                                            auto ___x_buf = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                            auto *_x_buf = ___x_buf.ptr<16>();

                                                                            {    ///////////////////
                                                                                int __dacesym_a = a;
                                                                                int __dacesym_ii = ii;
                                                                                int __dacesym_jj = jj;
                                                                                auto a = __dacesym_a;
                                                                                auto ii = __dacesym_ii;
                                                                                auto jj = __dacesym_jj;
                                                                                dace::vec<float, 1> buf_reg[1];
                                                                                #pragma HLS ARRAY_PARTITION variable=buf_reg complete
                                                                                dace::vec<float, 1> memBuf_A[16];
                                                                                #pragma HLS ARRAY_PARTITION variable=memBuf_A complete

                                                                                __state_partial_reduction_inner_1_init_state:
                                                                                {
                                                                                    dace::vec<float, 1> vecBuf_A[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=vecBuf_A complete
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(_A_unroll.pop()), vecBuf_A);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_A false
                                                                                    {
                                                                                        for (int k_stream = 0; k_stream < 16; k_stream += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (vecBuf_A + k_stream);
                                                                                                dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (memBuf_A + k_stream);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (streamToLocalA_map)
                                                                                                outCon = inCon;
                                                                                                ////////////////////

                                                                                                __outCon.write(outCon);
                                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    {
                                                                                        {
                                                                                            const int j_init = 0; // Degenerate loop
                                                                                            {

                                                                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg + j_init);
                                                                                                dace::vec<float, 1> out;

                                                                                                ////////////////////
                                                                                                // Tasklet code (init_buf_reg)
                                                                                                out = 0;
                                                                                                ////////////////////

                                                                                                __out.write(out);
                                                                                                #pragma HLS DEPENDENCE variable=out false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                if ((ii == 0)) {
                                                                                    __state_partial_reduction_inner_1_readX_state:
                                                                                    {
                                                                                        {
                                                                                            auto __inCon = _x_unroll;
                                                                                            auto inCon = __inCon.pop();

                                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf + jj);
                                                                                            dace::vec<float, 16> outCon;

                                                                                            ////////////////////
                                                                                            // Tasklet code (streamToLocal_map)
                                                                                            outCon = inCon;
                                                                                            ////////////////////

                                                                                            __outCon.write(outCon);
                                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                                        }
                                                                                    }
                                                                                    __state_exit_partial_reduction_inner_1_init_state_then:;
                                                                                    } else {
                                                                                    __state_partial_reduction_inner_1_readEmpty_state:
                                                                                    ;
                                                                                    __state_exit_partial_reduction_inner_1_init_state_else:;
                                                                                }
                                                                                __state_partial_reduction_inner_1_compute_state:
                                                                                {
                                                                                    dace::vec<float, 16> vecBuf_x;
                                                                                    dace::vec<float, 1> memBuf_x[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=memBuf_x complete
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf + jj);
                                                                                        dace::vec<float, 16> inCon = __inCon.val<16>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&vecBuf_x);
                                                                                        dace::vec<float, 16> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (streamToLocal_map)
                                                                                        outCon = inCon;
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(vecBuf_x), memBuf_x);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_x false
                                                                                    #pragma HLS DEPENDENCE variable=memBuf_x false
                                                                                    {
                                                                                        for (int j_inner = 0; j_inner < 16; j_inner += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __A_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_A + j_inner);
                                                                                                dace::vec<float, 1> A_con = __A_con.val<1>();
                                                                                                auto __x_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_x + j_inner);
                                                                                                dace::vec<float, 1> x_con = __x_con.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (compute_task)
                                                                                                outCon = ((a * A_con) * x_con);
                                                                                                ////////////////////

                                                                                                __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                __state_partial_reduction_inner_1_write_state:
                                                                                {
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (buf_reg);
                                                                                        dace::vec<float, 1> inCon = __inCon.val<1>();
                                                                                        auto __prevCon = dace::ArrayViewIn<float, 0, 1, 1> (_buf_in_unroll + (jj % 16));
                                                                                        dace::vec<float, 1> prevCon = __prevCon.val<1>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_out + (jj % 16));
                                                                                        dace::vec<float, 1> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (write_out_task)
                                                                                        outCon = (prevCon + inCon);
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                }
                                                                                __state_exit_partial_reduction_inner_1_sdfg:;
                                                                            }    ///////////////////

                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_1_red_reduceTile:
                                                            {
                                                                {
                                                                    for (int k = 0; k < 16; k += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (red_buf + k);
                                                                            dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (res_buf);
                                                                            dace::vec<float, 1> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (finalReduction)
                                                                            outCon = inCon;
                                                                            ////////////////////

                                                                            __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_1_store_reduceTile:
                                                            {
                                                                {
                                                                    auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (res_buf);
                                                                    dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                    auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                    dace::vec<float, 1> outCon;

                                                                    ////////////////////
                                                                    // Tasklet code (storeRed_task)
                                                                    outCon = inCon;
                                                                    ////////////////////

                                                                    __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                }
                                                            }
                                                            if ((j == ((n / 8192) - 1))) {
                                                                __state_redTile_sdfg_1_write_y_reduceTile:
                                                                {
                                                                    _res_red.push(dace::Read<float, 1>(_y_red + ii));
                                                                    #pragma HLS DEPENDENCE variable=_y_red false
                                                                }
                                                                __state_exit_redTile_sdfg_1_store_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_1_write_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_1_store_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_1_end_reduceTile:
                                                            ;
                                                            __state_exit_redTile_sdfg_1_sdfg:;
                                                        }    ///////////////////

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                __state_exit_yTile_sdfg_1_sdfg:;
                            }    ///////////////////

                        }
                    }
                }
            }
            __state_exit_gemv_fpga_stream_rowTiles_1_sdfg:;
        }    ///////////////////

    }
}

void module_saxpy_l1_2(dace::FIFO<float, 1, 32> &_res_to_saxpy_l1_2_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l1_2_y_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_y_0, float a, int n) {
    {
        auto ___x = dace::make_streamview(_res_to_saxpy_l1_2_x_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(_res_to_saxpy_l1_2_y_0);
        auto &_y = ___y;
        auto ___res = dace::make_streamview(_res_to_saxpy_y_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_vecAdd_graph_6_state_0:
            {
                {
                    for (int i = 0; i < n; i += 1) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS LOOP_FLATTEN
                        {
                            auto __x_con = _x;
                            auto x_con = __x_con.pop();
                            auto __y_con = _y;
                            auto y_con = __y_con.pop();

                            auto __z_con = _res;
                            dace::vec<float, 1> z_con;

                            ////////////////////
                            // Tasklet code (vecAdd_task)
                            z_con = ((a * x_con) + y_con);
                            ////////////////////

                            __z_con.write(z_con);
                        }
                    }
                }
            }
            __state_exit_vecAdd_graph_6_sdfg:;
        }    ///////////////////

    }
}

void module_GEMV2(dace::FIFO<float, 16, 32> &_RES_to_GEMV2_A_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_1_y_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV2_0, float a, int n) {
    {
        auto ___A = dace::make_streamview(_RES_to_GEMV2_A_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_gemv_GEMV2_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l2_1_y_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_gemv_fpga_stream_rowTiles_2_state_0:
            {
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            auto ___A_yTile = _A;
                            auto &_A_yTile = ___A_yTile;
                            auto ___x_yTile = _x;
                            auto &_x_yTile = ___x_yTile;
                            auto __yTile = _res;
                            auto &yTile = __yTile;

                            {    ///////////////////
                                int __dacesym_a = a;
                                int __dacesym_n = n;
                                auto a = __dacesym_a;
                                auto n = __dacesym_n;
                                dace::vec<float, 1> y_tileRes[8192];

                                __state_yTile_sdfg_2_yTile_init:
                                {
                                    {
                                        for (int j_init = 0; j_init < 8192; j_init += 1) {
                                            #pragma HLS UNROLL
                                            {

                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (y_tileRes + j_init);
                                                dace::vec<float, 1> out;

                                                ////////////////////
                                                // Tasklet code (init_y_tileRes)
                                                out = 0;
                                                ////////////////////

                                                __out.write(out);
                                                #pragma HLS DEPENDENCE variable=out false
                                            }
                                        }
                                    }
                                }
                                __state_yTile_sdfg_2_yTile_compute:
                                {
                                    {
                                        for (long long j = 0; j < (n / 8192); j += 1) {
                                            {
                                                for (int ii = 0; ii < 8192; ii += 1) {
                                                    {
                                                        auto ___A_red = _A_yTile;
                                                        auto &_A_red = ___A_red;
                                                        auto ___x_red = _x_yTile;
                                                        auto &_x_red = ___x_red;
                                                        auto ___y_red = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_tileRes, 1);
                                                        auto *_y_red = ___y_red.ptr<1>();
                                                        auto ___res_red = yTile;
                                                        auto &_res_red = ___res_red;

                                                        {    ///////////////////
                                                            int __dacesym_a = a;
                                                            int __dacesym_ii = ii;
                                                            int __dacesym_j = j;
                                                            int __dacesym_n = n;
                                                            auto a = __dacesym_a;
                                                            auto ii = __dacesym_ii;
                                                            auto j = __dacesym_j;
                                                            auto n = __dacesym_n;
                                                            dace::vec<float, 1> red_buf[16];
                                                            dace::vec<float, 1> res_buf[1];
                                                            #pragma HLS ARRAY_PARTITION variable=res_buf complete

                                                            __state_redTile_sdfg_2_init_reduceTile:
                                                            {
                                                                {
                                                                    for (int j_init = 0; j_init < 16; j_init += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (red_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_red_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                                {
                                                                    {
                                                                        const int j_init = 0; // Degenerate loop
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (res_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_res_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if ((j == 0)) {
                                                                __state_redTile_sdfg_2_read_y_reduceTile:
                                                                {
                                                                    {

                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                        dace::vec<float, 1> outCon;

                                                                        ////////////////////
                                                                        // Tasklet code (read_y_tasklet)
                                                                        outCon = 0;
                                                                        ////////////////////

                                                                        __outCon.write(outCon);
                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                    }
                                                                }
                                                                __state_exit_redTile_sdfg_2_init_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_2_read_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_2_init_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_2_compute_reduceTile:
                                                            {
                                                                dace::vec<float, 16> x_buf[(8192 / 16)];
                                                                {
                                                                    for (int jj = 0; jj < 512; jj += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto ___A_unroll = _A_red;
                                                                            auto &_A_unroll = ___A_unroll;
                                                                            auto ___x_unroll = _x_red;
                                                                            auto &_x_unroll = ___x_unroll;
                                                                            auto ___buf_in_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *_buf_in_unroll = ___buf_in_unroll.ptr<1>();
                                                                            auto __buf_out = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *buf_out = __buf_out.ptr<1>();
                                                                            auto ___x_buf = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                            auto *_x_buf = ___x_buf.ptr<16>();

                                                                            {    ///////////////////
                                                                                int __dacesym_a = a;
                                                                                int __dacesym_ii = ii;
                                                                                int __dacesym_jj = jj;
                                                                                auto a = __dacesym_a;
                                                                                auto ii = __dacesym_ii;
                                                                                auto jj = __dacesym_jj;
                                                                                dace::vec<float, 1> buf_reg[1];
                                                                                #pragma HLS ARRAY_PARTITION variable=buf_reg complete
                                                                                dace::vec<float, 1> memBuf_A[16];
                                                                                #pragma HLS ARRAY_PARTITION variable=memBuf_A complete

                                                                                __state_partial_reduction_inner_2_init_state:
                                                                                {
                                                                                    dace::vec<float, 1> vecBuf_A[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=vecBuf_A complete
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(_A_unroll.pop()), vecBuf_A);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_A false
                                                                                    {
                                                                                        for (int k_stream = 0; k_stream < 16; k_stream += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (vecBuf_A + k_stream);
                                                                                                dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (memBuf_A + k_stream);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (streamToLocalA_map)
                                                                                                outCon = inCon;
                                                                                                ////////////////////

                                                                                                __outCon.write(outCon);
                                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    {
                                                                                        {
                                                                                            const int j_init = 0; // Degenerate loop
                                                                                            {

                                                                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg + j_init);
                                                                                                dace::vec<float, 1> out;

                                                                                                ////////////////////
                                                                                                // Tasklet code (init_buf_reg)
                                                                                                out = 0;
                                                                                                ////////////////////

                                                                                                __out.write(out);
                                                                                                #pragma HLS DEPENDENCE variable=out false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                if ((ii == 0)) {
                                                                                    __state_partial_reduction_inner_2_readX_state:
                                                                                    {
                                                                                        {
                                                                                            auto __inCon = _x_unroll;
                                                                                            auto inCon = __inCon.pop();

                                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf + jj);
                                                                                            dace::vec<float, 16> outCon;

                                                                                            ////////////////////
                                                                                            // Tasklet code (streamToLocal_map)
                                                                                            outCon = inCon;
                                                                                            ////////////////////

                                                                                            __outCon.write(outCon);
                                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                                        }
                                                                                    }
                                                                                    __state_exit_partial_reduction_inner_2_init_state_then:;
                                                                                    } else {
                                                                                    __state_partial_reduction_inner_2_readEmpty_state:
                                                                                    ;
                                                                                    __state_exit_partial_reduction_inner_2_init_state_else:;
                                                                                }
                                                                                __state_partial_reduction_inner_2_compute_state:
                                                                                {
                                                                                    dace::vec<float, 16> vecBuf_x;
                                                                                    dace::vec<float, 1> memBuf_x[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=memBuf_x complete
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf + jj);
                                                                                        dace::vec<float, 16> inCon = __inCon.val<16>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&vecBuf_x);
                                                                                        dace::vec<float, 16> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (streamToLocal_map)
                                                                                        outCon = inCon;
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(vecBuf_x), memBuf_x);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_x false
                                                                                    #pragma HLS DEPENDENCE variable=memBuf_x false
                                                                                    {
                                                                                        for (int j_inner = 0; j_inner < 16; j_inner += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __A_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_A + j_inner);
                                                                                                dace::vec<float, 1> A_con = __A_con.val<1>();
                                                                                                auto __x_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_x + j_inner);
                                                                                                dace::vec<float, 1> x_con = __x_con.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (compute_task)
                                                                                                outCon = ((a * A_con) * x_con);
                                                                                                ////////////////////

                                                                                                __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                __state_partial_reduction_inner_2_write_state:
                                                                                {
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (buf_reg);
                                                                                        dace::vec<float, 1> inCon = __inCon.val<1>();
                                                                                        auto __prevCon = dace::ArrayViewIn<float, 0, 1, 1> (_buf_in_unroll + (jj % 16));
                                                                                        dace::vec<float, 1> prevCon = __prevCon.val<1>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_out + (jj % 16));
                                                                                        dace::vec<float, 1> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (write_out_task)
                                                                                        outCon = (prevCon + inCon);
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                }
                                                                                __state_exit_partial_reduction_inner_2_sdfg:;
                                                                            }    ///////////////////

                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_2_red_reduceTile:
                                                            {
                                                                {
                                                                    for (int k = 0; k < 16; k += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (red_buf + k);
                                                                            dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (res_buf);
                                                                            dace::vec<float, 1> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (finalReduction)
                                                                            outCon = inCon;
                                                                            ////////////////////

                                                                            __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_2_store_reduceTile:
                                                            {
                                                                {
                                                                    auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (res_buf);
                                                                    dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                    auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                    dace::vec<float, 1> outCon;

                                                                    ////////////////////
                                                                    // Tasklet code (storeRed_task)
                                                                    outCon = inCon;
                                                                    ////////////////////

                                                                    __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                }
                                                            }
                                                            if ((j == ((n / 8192) - 1))) {
                                                                __state_redTile_sdfg_2_write_y_reduceTile:
                                                                {
                                                                    _res_red.push(dace::Read<float, 1>(_y_red + ii));
                                                                    #pragma HLS DEPENDENCE variable=_y_red false
                                                                }
                                                                __state_exit_redTile_sdfg_2_store_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_2_write_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_2_store_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_2_end_reduceTile:
                                                            ;
                                                            __state_exit_redTile_sdfg_2_sdfg:;
                                                        }    ///////////////////

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                __state_exit_yTile_sdfg_2_sdfg:;
                            }    ///////////////////

                        }
                    }
                }
            }
            __state_exit_gemv_fpga_stream_rowTiles_2_sdfg:;
        }    ///////////////////

    }
}

void module_GEMV6(dace::FIFO<float, 16, 32> &_RES_to_GEMV6_A_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_3_y_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV6_0, float a, int n) {
    {
        auto ___A = dace::make_streamview(_RES_to_GEMV6_A_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_gemv_GEMV6_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l2_3_y_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_gemv_fpga_stream_rowTiles_6_state_0:
            {
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            auto ___A_yTile = _A;
                            auto &_A_yTile = ___A_yTile;
                            auto ___x_yTile = _x;
                            auto &_x_yTile = ___x_yTile;
                            auto __yTile = _res;
                            auto &yTile = __yTile;

                            {    ///////////////////
                                int __dacesym_a = a;
                                int __dacesym_n = n;
                                auto a = __dacesym_a;
                                auto n = __dacesym_n;
                                dace::vec<float, 1> y_tileRes[8192];

                                __state_yTile_sdfg_6_yTile_init:
                                {
                                    {
                                        for (int j_init = 0; j_init < 8192; j_init += 1) {
                                            #pragma HLS UNROLL
                                            {

                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (y_tileRes + j_init);
                                                dace::vec<float, 1> out;

                                                ////////////////////
                                                // Tasklet code (init_y_tileRes)
                                                out = 0;
                                                ////////////////////

                                                __out.write(out);
                                                #pragma HLS DEPENDENCE variable=out false
                                            }
                                        }
                                    }
                                }
                                __state_yTile_sdfg_6_yTile_compute:
                                {
                                    {
                                        for (long long j = 0; j < (n / 8192); j += 1) {
                                            {
                                                for (int ii = 0; ii < 8192; ii += 1) {
                                                    {
                                                        auto ___A_red = _A_yTile;
                                                        auto &_A_red = ___A_red;
                                                        auto ___x_red = _x_yTile;
                                                        auto &_x_red = ___x_red;
                                                        auto ___y_red = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_tileRes, 1);
                                                        auto *_y_red = ___y_red.ptr<1>();
                                                        auto ___res_red = yTile;
                                                        auto &_res_red = ___res_red;

                                                        {    ///////////////////
                                                            int __dacesym_a = a;
                                                            int __dacesym_ii = ii;
                                                            int __dacesym_j = j;
                                                            int __dacesym_n = n;
                                                            auto a = __dacesym_a;
                                                            auto ii = __dacesym_ii;
                                                            auto j = __dacesym_j;
                                                            auto n = __dacesym_n;
                                                            dace::vec<float, 1> red_buf[16];
                                                            dace::vec<float, 1> res_buf[1];
                                                            #pragma HLS ARRAY_PARTITION variable=res_buf complete

                                                            __state_redTile_sdfg_6_init_reduceTile:
                                                            {
                                                                {
                                                                    for (int j_init = 0; j_init < 16; j_init += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (red_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_red_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                                {
                                                                    {
                                                                        const int j_init = 0; // Degenerate loop
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (res_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_res_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if ((j == 0)) {
                                                                __state_redTile_sdfg_6_read_y_reduceTile:
                                                                {
                                                                    {

                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                        dace::vec<float, 1> outCon;

                                                                        ////////////////////
                                                                        // Tasklet code (read_y_tasklet)
                                                                        outCon = 0;
                                                                        ////////////////////

                                                                        __outCon.write(outCon);
                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                    }
                                                                }
                                                                __state_exit_redTile_sdfg_6_init_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_6_read_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_6_init_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_6_compute_reduceTile:
                                                            {
                                                                dace::vec<float, 16> x_buf[(8192 / 16)];
                                                                {
                                                                    for (int jj = 0; jj < 512; jj += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto ___A_unroll = _A_red;
                                                                            auto &_A_unroll = ___A_unroll;
                                                                            auto ___x_unroll = _x_red;
                                                                            auto &_x_unroll = ___x_unroll;
                                                                            auto ___buf_in_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *_buf_in_unroll = ___buf_in_unroll.ptr<1>();
                                                                            auto __buf_out = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *buf_out = __buf_out.ptr<1>();
                                                                            auto ___x_buf = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                            auto *_x_buf = ___x_buf.ptr<16>();

                                                                            {    ///////////////////
                                                                                int __dacesym_a = a;
                                                                                int __dacesym_ii = ii;
                                                                                int __dacesym_jj = jj;
                                                                                auto a = __dacesym_a;
                                                                                auto ii = __dacesym_ii;
                                                                                auto jj = __dacesym_jj;
                                                                                dace::vec<float, 1> buf_reg[1];
                                                                                #pragma HLS ARRAY_PARTITION variable=buf_reg complete
                                                                                dace::vec<float, 1> memBuf_A[16];
                                                                                #pragma HLS ARRAY_PARTITION variable=memBuf_A complete

                                                                                __state_partial_reduction_inner_6_init_state:
                                                                                {
                                                                                    dace::vec<float, 1> vecBuf_A[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=vecBuf_A complete
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(_A_unroll.pop()), vecBuf_A);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_A false
                                                                                    {
                                                                                        for (int k_stream = 0; k_stream < 16; k_stream += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (vecBuf_A + k_stream);
                                                                                                dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (memBuf_A + k_stream);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (streamToLocalA_map)
                                                                                                outCon = inCon;
                                                                                                ////////////////////

                                                                                                __outCon.write(outCon);
                                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    {
                                                                                        {
                                                                                            const int j_init = 0; // Degenerate loop
                                                                                            {

                                                                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg + j_init);
                                                                                                dace::vec<float, 1> out;

                                                                                                ////////////////////
                                                                                                // Tasklet code (init_buf_reg)
                                                                                                out = 0;
                                                                                                ////////////////////

                                                                                                __out.write(out);
                                                                                                #pragma HLS DEPENDENCE variable=out false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                if ((ii == 0)) {
                                                                                    __state_partial_reduction_inner_6_readX_state:
                                                                                    {
                                                                                        {
                                                                                            auto __inCon = _x_unroll;
                                                                                            auto inCon = __inCon.pop();

                                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf + jj);
                                                                                            dace::vec<float, 16> outCon;

                                                                                            ////////////////////
                                                                                            // Tasklet code (streamToLocal_map)
                                                                                            outCon = inCon;
                                                                                            ////////////////////

                                                                                            __outCon.write(outCon);
                                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                                        }
                                                                                    }
                                                                                    __state_exit_partial_reduction_inner_6_init_state_then:;
                                                                                    } else {
                                                                                    __state_partial_reduction_inner_6_readEmpty_state:
                                                                                    ;
                                                                                    __state_exit_partial_reduction_inner_6_init_state_else:;
                                                                                }
                                                                                __state_partial_reduction_inner_6_compute_state:
                                                                                {
                                                                                    dace::vec<float, 16> vecBuf_x;
                                                                                    dace::vec<float, 1> memBuf_x[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=memBuf_x complete
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf + jj);
                                                                                        dace::vec<float, 16> inCon = __inCon.val<16>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&vecBuf_x);
                                                                                        dace::vec<float, 16> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (streamToLocal_map)
                                                                                        outCon = inCon;
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(vecBuf_x), memBuf_x);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_x false
                                                                                    #pragma HLS DEPENDENCE variable=memBuf_x false
                                                                                    {
                                                                                        for (int j_inner = 0; j_inner < 16; j_inner += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __A_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_A + j_inner);
                                                                                                dace::vec<float, 1> A_con = __A_con.val<1>();
                                                                                                auto __x_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_x + j_inner);
                                                                                                dace::vec<float, 1> x_con = __x_con.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (compute_task)
                                                                                                outCon = ((a * A_con) * x_con);
                                                                                                ////////////////////

                                                                                                __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                __state_partial_reduction_inner_6_write_state:
                                                                                {
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (buf_reg);
                                                                                        dace::vec<float, 1> inCon = __inCon.val<1>();
                                                                                        auto __prevCon = dace::ArrayViewIn<float, 0, 1, 1> (_buf_in_unroll + (jj % 16));
                                                                                        dace::vec<float, 1> prevCon = __prevCon.val<1>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_out + (jj % 16));
                                                                                        dace::vec<float, 1> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (write_out_task)
                                                                                        outCon = (prevCon + inCon);
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                }
                                                                                __state_exit_partial_reduction_inner_6_sdfg:;
                                                                            }    ///////////////////

                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_6_red_reduceTile:
                                                            {
                                                                {
                                                                    for (int k = 0; k < 16; k += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (red_buf + k);
                                                                            dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (res_buf);
                                                                            dace::vec<float, 1> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (finalReduction)
                                                                            outCon = inCon;
                                                                            ////////////////////

                                                                            __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_6_store_reduceTile:
                                                            {
                                                                {
                                                                    auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (res_buf);
                                                                    dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                    auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                    dace::vec<float, 1> outCon;

                                                                    ////////////////////
                                                                    // Tasklet code (storeRed_task)
                                                                    outCon = inCon;
                                                                    ////////////////////

                                                                    __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                }
                                                            }
                                                            if ((j == ((n / 8192) - 1))) {
                                                                __state_redTile_sdfg_6_write_y_reduceTile:
                                                                {
                                                                    _res_red.push(dace::Read<float, 1>(_y_red + ii));
                                                                    #pragma HLS DEPENDENCE variable=_y_red false
                                                                }
                                                                __state_exit_redTile_sdfg_6_store_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_6_write_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_6_store_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_6_end_reduceTile:
                                                            ;
                                                            __state_exit_redTile_sdfg_6_sdfg:;
                                                        }    ///////////////////

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                __state_exit_yTile_sdfg_6_sdfg:;
                            }    ///////////////////

                        }
                    }
                }
            }
            __state_exit_gemv_fpga_stream_rowTiles_6_sdfg:;
        }    ///////////////////

    }
}

void module_saxpy_l2_1(dace::FIFO<float, 1, 32> &_res_to_saxpy_l1_1_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_1_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_1_y_0, float a, int n) {
    {
        auto ___x = dace::make_streamview(_res_to_saxpy_l2_1_x_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(_res_to_saxpy_l2_1_y_0);
        auto &_y = ___y;
        auto ___res = dace::make_streamview(_res_to_saxpy_l1_1_x_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_vecAdd_graph_1_state_0:
            {
                {
                    for (int i = 0; i < n; i += 1) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS LOOP_FLATTEN
                        {
                            auto __x_con = _x;
                            auto x_con = __x_con.pop();
                            auto __y_con = _y;
                            auto y_con = __y_con.pop();

                            auto __z_con = _res;
                            dace::vec<float, 1> z_con;

                            ////////////////////
                            // Tasklet code (vecAdd_task)
                            z_con = ((a * x_con) + y_con);
                            ////////////////////

                            __z_con.write(z_con);
                        }
                    }
                }
            }
            __state_exit_vecAdd_graph_1_sdfg:;
        }    ///////////////////

    }
}

void module_GEMV3(dace::FIFO<float, 16, 32> &_RES_to_GEMV3_A_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_2_x_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV3_0, float a, int n) {
    {
        auto ___A = dace::make_streamview(_RES_to_GEMV3_A_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_gemv_GEMV3_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l2_2_x_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_gemv_fpga_stream_rowTiles_3_state_0:
            {
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            auto ___A_yTile = _A;
                            auto &_A_yTile = ___A_yTile;
                            auto ___x_yTile = _x;
                            auto &_x_yTile = ___x_yTile;
                            auto __yTile = _res;
                            auto &yTile = __yTile;

                            {    ///////////////////
                                int __dacesym_a = a;
                                int __dacesym_n = n;
                                auto a = __dacesym_a;
                                auto n = __dacesym_n;
                                dace::vec<float, 1> y_tileRes[8192];

                                __state_yTile_sdfg_3_yTile_init:
                                {
                                    {
                                        for (int j_init = 0; j_init < 8192; j_init += 1) {
                                            #pragma HLS UNROLL
                                            {

                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (y_tileRes + j_init);
                                                dace::vec<float, 1> out;

                                                ////////////////////
                                                // Tasklet code (init_y_tileRes)
                                                out = 0;
                                                ////////////////////

                                                __out.write(out);
                                                #pragma HLS DEPENDENCE variable=out false
                                            }
                                        }
                                    }
                                }
                                __state_yTile_sdfg_3_yTile_compute:
                                {
                                    {
                                        for (long long j = 0; j < (n / 8192); j += 1) {
                                            {
                                                for (int ii = 0; ii < 8192; ii += 1) {
                                                    {
                                                        auto ___A_red = _A_yTile;
                                                        auto &_A_red = ___A_red;
                                                        auto ___x_red = _x_yTile;
                                                        auto &_x_red = ___x_red;
                                                        auto ___y_red = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_tileRes, 1);
                                                        auto *_y_red = ___y_red.ptr<1>();
                                                        auto ___res_red = yTile;
                                                        auto &_res_red = ___res_red;

                                                        {    ///////////////////
                                                            int __dacesym_a = a;
                                                            int __dacesym_ii = ii;
                                                            int __dacesym_j = j;
                                                            int __dacesym_n = n;
                                                            auto a = __dacesym_a;
                                                            auto ii = __dacesym_ii;
                                                            auto j = __dacesym_j;
                                                            auto n = __dacesym_n;
                                                            dace::vec<float, 1> red_buf[16];
                                                            dace::vec<float, 1> res_buf[1];
                                                            #pragma HLS ARRAY_PARTITION variable=res_buf complete

                                                            __state_redTile_sdfg_3_init_reduceTile:
                                                            {
                                                                {
                                                                    for (int j_init = 0; j_init < 16; j_init += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (red_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_red_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                                {
                                                                    {
                                                                        const int j_init = 0; // Degenerate loop
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (res_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_res_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if ((j == 0)) {
                                                                __state_redTile_sdfg_3_read_y_reduceTile:
                                                                {
                                                                    {

                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                        dace::vec<float, 1> outCon;

                                                                        ////////////////////
                                                                        // Tasklet code (read_y_tasklet)
                                                                        outCon = 0;
                                                                        ////////////////////

                                                                        __outCon.write(outCon);
                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                    }
                                                                }
                                                                __state_exit_redTile_sdfg_3_init_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_3_read_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_3_init_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_3_compute_reduceTile:
                                                            {
                                                                dace::vec<float, 16> x_buf[(8192 / 16)];
                                                                {
                                                                    for (int jj = 0; jj < 512; jj += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto ___A_unroll = _A_red;
                                                                            auto &_A_unroll = ___A_unroll;
                                                                            auto ___x_unroll = _x_red;
                                                                            auto &_x_unroll = ___x_unroll;
                                                                            auto ___buf_in_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *_buf_in_unroll = ___buf_in_unroll.ptr<1>();
                                                                            auto __buf_out = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *buf_out = __buf_out.ptr<1>();
                                                                            auto ___x_buf = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                            auto *_x_buf = ___x_buf.ptr<16>();

                                                                            {    ///////////////////
                                                                                int __dacesym_a = a;
                                                                                int __dacesym_ii = ii;
                                                                                int __dacesym_jj = jj;
                                                                                auto a = __dacesym_a;
                                                                                auto ii = __dacesym_ii;
                                                                                auto jj = __dacesym_jj;
                                                                                dace::vec<float, 1> buf_reg[1];
                                                                                #pragma HLS ARRAY_PARTITION variable=buf_reg complete
                                                                                dace::vec<float, 1> memBuf_A[16];
                                                                                #pragma HLS ARRAY_PARTITION variable=memBuf_A complete

                                                                                __state_partial_reduction_inner_3_init_state:
                                                                                {
                                                                                    dace::vec<float, 1> vecBuf_A[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=vecBuf_A complete
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(_A_unroll.pop()), vecBuf_A);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_A false
                                                                                    {
                                                                                        for (int k_stream = 0; k_stream < 16; k_stream += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (vecBuf_A + k_stream);
                                                                                                dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (memBuf_A + k_stream);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (streamToLocalA_map)
                                                                                                outCon = inCon;
                                                                                                ////////////////////

                                                                                                __outCon.write(outCon);
                                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    {
                                                                                        {
                                                                                            const int j_init = 0; // Degenerate loop
                                                                                            {

                                                                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg + j_init);
                                                                                                dace::vec<float, 1> out;

                                                                                                ////////////////////
                                                                                                // Tasklet code (init_buf_reg)
                                                                                                out = 0;
                                                                                                ////////////////////

                                                                                                __out.write(out);
                                                                                                #pragma HLS DEPENDENCE variable=out false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                if ((ii == 0)) {
                                                                                    __state_partial_reduction_inner_3_readX_state:
                                                                                    {
                                                                                        {
                                                                                            auto __inCon = _x_unroll;
                                                                                            auto inCon = __inCon.pop();

                                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf + jj);
                                                                                            dace::vec<float, 16> outCon;

                                                                                            ////////////////////
                                                                                            // Tasklet code (streamToLocal_map)
                                                                                            outCon = inCon;
                                                                                            ////////////////////

                                                                                            __outCon.write(outCon);
                                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                                        }
                                                                                    }
                                                                                    __state_exit_partial_reduction_inner_3_init_state_then:;
                                                                                    } else {
                                                                                    __state_partial_reduction_inner_3_readEmpty_state:
                                                                                    ;
                                                                                    __state_exit_partial_reduction_inner_3_init_state_else:;
                                                                                }
                                                                                __state_partial_reduction_inner_3_compute_state:
                                                                                {
                                                                                    dace::vec<float, 16> vecBuf_x;
                                                                                    dace::vec<float, 1> memBuf_x[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=memBuf_x complete
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf + jj);
                                                                                        dace::vec<float, 16> inCon = __inCon.val<16>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&vecBuf_x);
                                                                                        dace::vec<float, 16> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (streamToLocal_map)
                                                                                        outCon = inCon;
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(vecBuf_x), memBuf_x);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_x false
                                                                                    #pragma HLS DEPENDENCE variable=memBuf_x false
                                                                                    {
                                                                                        for (int j_inner = 0; j_inner < 16; j_inner += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __A_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_A + j_inner);
                                                                                                dace::vec<float, 1> A_con = __A_con.val<1>();
                                                                                                auto __x_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_x + j_inner);
                                                                                                dace::vec<float, 1> x_con = __x_con.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (compute_task)
                                                                                                outCon = ((a * A_con) * x_con);
                                                                                                ////////////////////

                                                                                                __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                __state_partial_reduction_inner_3_write_state:
                                                                                {
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (buf_reg);
                                                                                        dace::vec<float, 1> inCon = __inCon.val<1>();
                                                                                        auto __prevCon = dace::ArrayViewIn<float, 0, 1, 1> (_buf_in_unroll + (jj % 16));
                                                                                        dace::vec<float, 1> prevCon = __prevCon.val<1>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_out + (jj % 16));
                                                                                        dace::vec<float, 1> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (write_out_task)
                                                                                        outCon = (prevCon + inCon);
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                }
                                                                                __state_exit_partial_reduction_inner_3_sdfg:;
                                                                            }    ///////////////////

                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_3_red_reduceTile:
                                                            {
                                                                {
                                                                    for (int k = 0; k < 16; k += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (red_buf + k);
                                                                            dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (res_buf);
                                                                            dace::vec<float, 1> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (finalReduction)
                                                                            outCon = inCon;
                                                                            ////////////////////

                                                                            __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_3_store_reduceTile:
                                                            {
                                                                {
                                                                    auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (res_buf);
                                                                    dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                    auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                    dace::vec<float, 1> outCon;

                                                                    ////////////////////
                                                                    // Tasklet code (storeRed_task)
                                                                    outCon = inCon;
                                                                    ////////////////////

                                                                    __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                }
                                                            }
                                                            if ((j == ((n / 8192) - 1))) {
                                                                __state_redTile_sdfg_3_write_y_reduceTile:
                                                                {
                                                                    _res_red.push(dace::Read<float, 1>(_y_red + ii));
                                                                    #pragma HLS DEPENDENCE variable=_y_red false
                                                                }
                                                                __state_exit_redTile_sdfg_3_store_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_3_write_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_3_store_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_3_end_reduceTile:
                                                            ;
                                                            __state_exit_redTile_sdfg_3_sdfg:;
                                                        }    ///////////////////

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                __state_exit_yTile_sdfg_3_sdfg:;
                            }    ///////////////////

                        }
                    }
                }
            }
            __state_exit_gemv_fpga_stream_rowTiles_3_sdfg:;
        }    ///////////////////

    }
}

void module_saxpy_l2_3(dace::FIFO<float, 1, 32> &_res_to_saxpy_l1_2_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_3_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_3_y_0, float a, int n) {
    {
        auto ___y = dace::make_streamview(_res_to_saxpy_l2_3_y_0);
        auto &_y = ___y;
        auto ___x = dace::make_streamview(_res_to_saxpy_l2_3_x_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l1_2_x_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_vecAdd_graph_3_state_0:
            {
                {
                    for (int i = 0; i < n; i += 1) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS LOOP_FLATTEN
                        {
                            auto __x_con = _x;
                            auto x_con = __x_con.pop();
                            auto __y_con = _y;
                            auto y_con = __y_con.pop();

                            auto __z_con = _res;
                            dace::vec<float, 1> z_con;

                            ////////////////////
                            // Tasklet code (vecAdd_task)
                            z_con = ((a * x_con) + y_con);
                            ////////////////////

                            __z_con.write(z_con);
                        }
                    }
                }
            }
            __state_exit_vecAdd_graph_3_sdfg:;
        }    ///////////////////

    }
}

void module_GEMV5(dace::FIFO<float, 16, 32> &_RES_to_GEMV5_A_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_3_x_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV5_0, float a, int n) {
    {
        auto ___A = dace::make_streamview(_RES_to_GEMV5_A_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_gemv_GEMV5_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l2_3_x_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_gemv_fpga_stream_rowTiles_5_state_0:
            {
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            auto ___A_yTile = _A;
                            auto &_A_yTile = ___A_yTile;
                            auto ___x_yTile = _x;
                            auto &_x_yTile = ___x_yTile;
                            auto __yTile = _res;
                            auto &yTile = __yTile;

                            {    ///////////////////
                                int __dacesym_a = a;
                                int __dacesym_n = n;
                                auto a = __dacesym_a;
                                auto n = __dacesym_n;
                                dace::vec<float, 1> y_tileRes[8192];

                                __state_yTile_sdfg_5_yTile_init:
                                {
                                    {
                                        for (int j_init = 0; j_init < 8192; j_init += 1) {
                                            #pragma HLS UNROLL
                                            {

                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (y_tileRes + j_init);
                                                dace::vec<float, 1> out;

                                                ////////////////////
                                                // Tasklet code (init_y_tileRes)
                                                out = 0;
                                                ////////////////////

                                                __out.write(out);
                                                #pragma HLS DEPENDENCE variable=out false
                                            }
                                        }
                                    }
                                }
                                __state_yTile_sdfg_5_yTile_compute:
                                {
                                    {
                                        for (long long j = 0; j < (n / 8192); j += 1) {
                                            {
                                                for (int ii = 0; ii < 8192; ii += 1) {
                                                    {
                                                        auto ___A_red = _A_yTile;
                                                        auto &_A_red = ___A_red;
                                                        auto ___x_red = _x_yTile;
                                                        auto &_x_red = ___x_red;
                                                        auto ___y_red = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_tileRes, 1);
                                                        auto *_y_red = ___y_red.ptr<1>();
                                                        auto ___res_red = yTile;
                                                        auto &_res_red = ___res_red;

                                                        {    ///////////////////
                                                            int __dacesym_a = a;
                                                            int __dacesym_ii = ii;
                                                            int __dacesym_j = j;
                                                            int __dacesym_n = n;
                                                            auto a = __dacesym_a;
                                                            auto ii = __dacesym_ii;
                                                            auto j = __dacesym_j;
                                                            auto n = __dacesym_n;
                                                            dace::vec<float, 1> red_buf[16];
                                                            dace::vec<float, 1> res_buf[1];
                                                            #pragma HLS ARRAY_PARTITION variable=res_buf complete

                                                            __state_redTile_sdfg_5_init_reduceTile:
                                                            {
                                                                {
                                                                    for (int j_init = 0; j_init < 16; j_init += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (red_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_red_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                                {
                                                                    {
                                                                        const int j_init = 0; // Degenerate loop
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (res_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_res_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if ((j == 0)) {
                                                                __state_redTile_sdfg_5_read_y_reduceTile:
                                                                {
                                                                    {

                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                        dace::vec<float, 1> outCon;

                                                                        ////////////////////
                                                                        // Tasklet code (read_y_tasklet)
                                                                        outCon = 0;
                                                                        ////////////////////

                                                                        __outCon.write(outCon);
                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                    }
                                                                }
                                                                __state_exit_redTile_sdfg_5_init_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_5_read_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_5_init_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_5_compute_reduceTile:
                                                            {
                                                                dace::vec<float, 16> x_buf[(8192 / 16)];
                                                                {
                                                                    for (int jj = 0; jj < 512; jj += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto ___A_unroll = _A_red;
                                                                            auto &_A_unroll = ___A_unroll;
                                                                            auto ___x_unroll = _x_red;
                                                                            auto &_x_unroll = ___x_unroll;
                                                                            auto ___buf_in_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *_buf_in_unroll = ___buf_in_unroll.ptr<1>();
                                                                            auto __buf_out = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *buf_out = __buf_out.ptr<1>();
                                                                            auto ___x_buf = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                            auto *_x_buf = ___x_buf.ptr<16>();

                                                                            {    ///////////////////
                                                                                int __dacesym_a = a;
                                                                                int __dacesym_ii = ii;
                                                                                int __dacesym_jj = jj;
                                                                                auto a = __dacesym_a;
                                                                                auto ii = __dacesym_ii;
                                                                                auto jj = __dacesym_jj;
                                                                                dace::vec<float, 1> buf_reg[1];
                                                                                #pragma HLS ARRAY_PARTITION variable=buf_reg complete
                                                                                dace::vec<float, 1> memBuf_A[16];
                                                                                #pragma HLS ARRAY_PARTITION variable=memBuf_A complete

                                                                                __state_partial_reduction_inner_5_init_state:
                                                                                {
                                                                                    dace::vec<float, 1> vecBuf_A[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=vecBuf_A complete
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(_A_unroll.pop()), vecBuf_A);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_A false
                                                                                    {
                                                                                        for (int k_stream = 0; k_stream < 16; k_stream += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (vecBuf_A + k_stream);
                                                                                                dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (memBuf_A + k_stream);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (streamToLocalA_map)
                                                                                                outCon = inCon;
                                                                                                ////////////////////

                                                                                                __outCon.write(outCon);
                                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    {
                                                                                        {
                                                                                            const int j_init = 0; // Degenerate loop
                                                                                            {

                                                                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg + j_init);
                                                                                                dace::vec<float, 1> out;

                                                                                                ////////////////////
                                                                                                // Tasklet code (init_buf_reg)
                                                                                                out = 0;
                                                                                                ////////////////////

                                                                                                __out.write(out);
                                                                                                #pragma HLS DEPENDENCE variable=out false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                if ((ii == 0)) {
                                                                                    __state_partial_reduction_inner_5_readX_state:
                                                                                    {
                                                                                        {
                                                                                            auto __inCon = _x_unroll;
                                                                                            auto inCon = __inCon.pop();

                                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf + jj);
                                                                                            dace::vec<float, 16> outCon;

                                                                                            ////////////////////
                                                                                            // Tasklet code (streamToLocal_map)
                                                                                            outCon = inCon;
                                                                                            ////////////////////

                                                                                            __outCon.write(outCon);
                                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                                        }
                                                                                    }
                                                                                    __state_exit_partial_reduction_inner_5_init_state_then:;
                                                                                    } else {
                                                                                    __state_partial_reduction_inner_5_readEmpty_state:
                                                                                    ;
                                                                                    __state_exit_partial_reduction_inner_5_init_state_else:;
                                                                                }
                                                                                __state_partial_reduction_inner_5_compute_state:
                                                                                {
                                                                                    dace::vec<float, 16> vecBuf_x;
                                                                                    dace::vec<float, 1> memBuf_x[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=memBuf_x complete
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf + jj);
                                                                                        dace::vec<float, 16> inCon = __inCon.val<16>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&vecBuf_x);
                                                                                        dace::vec<float, 16> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (streamToLocal_map)
                                                                                        outCon = inCon;
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(vecBuf_x), memBuf_x);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_x false
                                                                                    #pragma HLS DEPENDENCE variable=memBuf_x false
                                                                                    {
                                                                                        for (int j_inner = 0; j_inner < 16; j_inner += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __A_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_A + j_inner);
                                                                                                dace::vec<float, 1> A_con = __A_con.val<1>();
                                                                                                auto __x_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_x + j_inner);
                                                                                                dace::vec<float, 1> x_con = __x_con.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (compute_task)
                                                                                                outCon = ((a * A_con) * x_con);
                                                                                                ////////////////////

                                                                                                __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                __state_partial_reduction_inner_5_write_state:
                                                                                {
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (buf_reg);
                                                                                        dace::vec<float, 1> inCon = __inCon.val<1>();
                                                                                        auto __prevCon = dace::ArrayViewIn<float, 0, 1, 1> (_buf_in_unroll + (jj % 16));
                                                                                        dace::vec<float, 1> prevCon = __prevCon.val<1>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_out + (jj % 16));
                                                                                        dace::vec<float, 1> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (write_out_task)
                                                                                        outCon = (prevCon + inCon);
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                }
                                                                                __state_exit_partial_reduction_inner_5_sdfg:;
                                                                            }    ///////////////////

                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_5_red_reduceTile:
                                                            {
                                                                {
                                                                    for (int k = 0; k < 16; k += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (red_buf + k);
                                                                            dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (res_buf);
                                                                            dace::vec<float, 1> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (finalReduction)
                                                                            outCon = inCon;
                                                                            ////////////////////

                                                                            __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_5_store_reduceTile:
                                                            {
                                                                {
                                                                    auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (res_buf);
                                                                    dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                    auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                    dace::vec<float, 1> outCon;

                                                                    ////////////////////
                                                                    // Tasklet code (storeRed_task)
                                                                    outCon = inCon;
                                                                    ////////////////////

                                                                    __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                }
                                                            }
                                                            if ((j == ((n / 8192) - 1))) {
                                                                __state_redTile_sdfg_5_write_y_reduceTile:
                                                                {
                                                                    _res_red.push(dace::Read<float, 1>(_y_red + ii));
                                                                    #pragma HLS DEPENDENCE variable=_y_red false
                                                                }
                                                                __state_exit_redTile_sdfg_5_store_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_5_write_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_5_store_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_5_end_reduceTile:
                                                            ;
                                                            __state_exit_redTile_sdfg_5_sdfg:;
                                                        }    ///////////////////

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                __state_exit_yTile_sdfg_5_sdfg:;
                            }    ///////////////////

                        }
                    }
                }
            }
            __state_exit_gemv_fpga_stream_rowTiles_5_sdfg:;
        }    ///////////////////

    }
}

void module_saxpy(dace::FIFO<float, 1, 32> &_res_to_blas_asum_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_y_0, float a, int n) {
    {
        auto ___y = dace::make_streamview(_res_to_saxpy_y_0);
        auto &_y = ___y;
        auto ___x = dace::make_streamview(_res_to_saxpy_x_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_blas_asum_x_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_vecAdd_graph_state_0:
            {
                {
                    for (int i = 0; i < n; i += 1) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS LOOP_FLATTEN
                        {
                            auto __x_con = _x;
                            auto x_con = __x_con.pop();
                            auto __y_con = _y;
                            auto y_con = __y_con.pop();

                            auto __z_con = _res;
                            dace::vec<float, 1> z_con;

                            ////////////////////
                            // Tasklet code (vecAdd_task)
                            z_con = ((a * x_con) + y_con);
                            ////////////////////

                            __z_con.write(z_con);
                        }
                    }
                }
            }
            __state_exit_vecAdd_graph_sdfg:;
        }    ///////////////////

    }
}

void module_GEMV7(dace::FIFO<float, 16, 32> &_RES_to_GEMV7_A_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_4_x_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV7_0, float a, int n) {
    {
        auto ___A = dace::make_streamview(_RES_to_GEMV7_A_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_gemv_GEMV7_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l2_4_x_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_gemv_fpga_stream_rowTiles_7_state_0:
            {
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            auto ___A_yTile = _A;
                            auto &_A_yTile = ___A_yTile;
                            auto ___x_yTile = _x;
                            auto &_x_yTile = ___x_yTile;
                            auto __yTile = _res;
                            auto &yTile = __yTile;

                            {    ///////////////////
                                int __dacesym_a = a;
                                int __dacesym_n = n;
                                auto a = __dacesym_a;
                                auto n = __dacesym_n;
                                dace::vec<float, 1> y_tileRes[8192];

                                __state_yTile_sdfg_7_yTile_init:
                                {
                                    {
                                        for (int j_init = 0; j_init < 8192; j_init += 1) {
                                            #pragma HLS UNROLL
                                            {

                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (y_tileRes + j_init);
                                                dace::vec<float, 1> out;

                                                ////////////////////
                                                // Tasklet code (init_y_tileRes)
                                                out = 0;
                                                ////////////////////

                                                __out.write(out);
                                                #pragma HLS DEPENDENCE variable=out false
                                            }
                                        }
                                    }
                                }
                                __state_yTile_sdfg_7_yTile_compute:
                                {
                                    {
                                        for (long long j = 0; j < (n / 8192); j += 1) {
                                            {
                                                for (int ii = 0; ii < 8192; ii += 1) {
                                                    {
                                                        auto ___A_red = _A_yTile;
                                                        auto &_A_red = ___A_red;
                                                        auto ___x_red = _x_yTile;
                                                        auto &_x_red = ___x_red;
                                                        auto ___y_red = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_tileRes, 1);
                                                        auto *_y_red = ___y_red.ptr<1>();
                                                        auto ___res_red = yTile;
                                                        auto &_res_red = ___res_red;

                                                        {    ///////////////////
                                                            int __dacesym_a = a;
                                                            int __dacesym_ii = ii;
                                                            int __dacesym_j = j;
                                                            int __dacesym_n = n;
                                                            auto a = __dacesym_a;
                                                            auto ii = __dacesym_ii;
                                                            auto j = __dacesym_j;
                                                            auto n = __dacesym_n;
                                                            dace::vec<float, 1> red_buf[16];
                                                            dace::vec<float, 1> res_buf[1];
                                                            #pragma HLS ARRAY_PARTITION variable=res_buf complete

                                                            __state_redTile_sdfg_7_init_reduceTile:
                                                            {
                                                                {
                                                                    for (int j_init = 0; j_init < 16; j_init += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (red_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_red_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                                {
                                                                    {
                                                                        const int j_init = 0; // Degenerate loop
                                                                        {

                                                                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (res_buf + j_init);
                                                                            dace::vec<float, 1> out;

                                                                            ////////////////////
                                                                            // Tasklet code (init_res_buf)
                                                                            out = 0;
                                                                            ////////////////////

                                                                            __out.write(out);
                                                                            #pragma HLS DEPENDENCE variable=out false
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if ((j == 0)) {
                                                                __state_redTile_sdfg_7_read_y_reduceTile:
                                                                {
                                                                    {

                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                        dace::vec<float, 1> outCon;

                                                                        ////////////////////
                                                                        // Tasklet code (read_y_tasklet)
                                                                        outCon = 0;
                                                                        ////////////////////

                                                                        __outCon.write(outCon);
                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                    }
                                                                }
                                                                __state_exit_redTile_sdfg_7_init_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_7_read_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_7_init_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_7_compute_reduceTile:
                                                            {
                                                                dace::vec<float, 16> x_buf[(8192 / 16)];
                                                                {
                                                                    for (int jj = 0; jj < 512; jj += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto ___A_unroll = _A_red;
                                                                            auto &_A_unroll = ___A_unroll;
                                                                            auto ___x_unroll = _x_red;
                                                                            auto &_x_unroll = ___x_unroll;
                                                                            auto ___buf_in_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *_buf_in_unroll = ___buf_in_unroll.ptr<1>();
                                                                            auto __buf_out = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                                                                            auto *buf_out = __buf_out.ptr<1>();
                                                                            auto ___x_buf = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                            auto *_x_buf = ___x_buf.ptr<16>();

                                                                            {    ///////////////////
                                                                                int __dacesym_a = a;
                                                                                int __dacesym_ii = ii;
                                                                                int __dacesym_jj = jj;
                                                                                auto a = __dacesym_a;
                                                                                auto ii = __dacesym_ii;
                                                                                auto jj = __dacesym_jj;
                                                                                dace::vec<float, 1> buf_reg[1];
                                                                                #pragma HLS ARRAY_PARTITION variable=buf_reg complete
                                                                                dace::vec<float, 1> memBuf_A[16];
                                                                                #pragma HLS ARRAY_PARTITION variable=memBuf_A complete

                                                                                __state_partial_reduction_inner_7_init_state:
                                                                                {
                                                                                    dace::vec<float, 1> vecBuf_A[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=vecBuf_A complete
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(_A_unroll.pop()), vecBuf_A);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_A false
                                                                                    {
                                                                                        for (int k_stream = 0; k_stream < 16; k_stream += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (vecBuf_A + k_stream);
                                                                                                dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (memBuf_A + k_stream);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (streamToLocalA_map)
                                                                                                outCon = inCon;
                                                                                                ////////////////////

                                                                                                __outCon.write(outCon);
                                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    {
                                                                                        {
                                                                                            const int j_init = 0; // Degenerate loop
                                                                                            {

                                                                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg + j_init);
                                                                                                dace::vec<float, 1> out;

                                                                                                ////////////////////
                                                                                                // Tasklet code (init_buf_reg)
                                                                                                out = 0;
                                                                                                ////////////////////

                                                                                                __out.write(out);
                                                                                                #pragma HLS DEPENDENCE variable=out false
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                if ((ii == 0)) {
                                                                                    __state_partial_reduction_inner_7_readX_state:
                                                                                    {
                                                                                        {
                                                                                            auto __inCon = _x_unroll;
                                                                                            auto inCon = __inCon.pop();

                                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf + jj);
                                                                                            dace::vec<float, 16> outCon;

                                                                                            ////////////////////
                                                                                            // Tasklet code (streamToLocal_map)
                                                                                            outCon = inCon;
                                                                                            ////////////////////

                                                                                            __outCon.write(outCon);
                                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                                        }
                                                                                    }
                                                                                    __state_exit_partial_reduction_inner_7_init_state_then:;
                                                                                    } else {
                                                                                    __state_partial_reduction_inner_7_readEmpty_state:
                                                                                    ;
                                                                                    __state_exit_partial_reduction_inner_7_init_state_else:;
                                                                                }
                                                                                __state_partial_reduction_inner_7_compute_state:
                                                                                {
                                                                                    dace::vec<float, 16> vecBuf_x;
                                                                                    dace::vec<float, 1> memBuf_x[16];
                                                                                    #pragma HLS ARRAY_PARTITION variable=memBuf_x complete
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf + jj);
                                                                                        dace::vec<float, 16> inCon = __inCon.val<16>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&vecBuf_x);
                                                                                        dace::vec<float, 16> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (streamToLocal_map)
                                                                                        outCon = inCon;
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                    dace::Unpack<float, 16>(dace::Read<float, 16>(vecBuf_x), memBuf_x);
                                                                                    #pragma HLS DEPENDENCE variable=vecBuf_x false
                                                                                    #pragma HLS DEPENDENCE variable=memBuf_x false
                                                                                    {
                                                                                        for (int j_inner = 0; j_inner < 16; j_inner += 1) {
                                                                                            #pragma HLS UNROLL
                                                                                            {
                                                                                                auto __A_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_A + j_inner);
                                                                                                dace::vec<float, 1> A_con = __A_con.val<1>();
                                                                                                auto __x_con = dace::ArrayViewIn<float, 0, 1, 1> (memBuf_x + j_inner);
                                                                                                dace::vec<float, 1> x_con = __x_con.val<1>();

                                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_reg);
                                                                                                dace::vec<float, 1> outCon;

                                                                                                ////////////////////
                                                                                                // Tasklet code (compute_task)
                                                                                                outCon = ((a * A_con) * x_con);
                                                                                                ////////////////////

                                                                                                __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                __state_partial_reduction_inner_7_write_state:
                                                                                {
                                                                                    {
                                                                                        auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (buf_reg);
                                                                                        dace::vec<float, 1> inCon = __inCon.val<1>();
                                                                                        auto __prevCon = dace::ArrayViewIn<float, 0, 1, 1> (_buf_in_unroll + (jj % 16));
                                                                                        dace::vec<float, 1> prevCon = __prevCon.val<1>();

                                                                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (buf_out + (jj % 16));
                                                                                        dace::vec<float, 1> outCon;

                                                                                        ////////////////////
                                                                                        // Tasklet code (write_out_task)
                                                                                        outCon = (prevCon + inCon);
                                                                                        ////////////////////

                                                                                        __outCon.write(outCon);
                                                                                        #pragma HLS DEPENDENCE variable=outCon false
                                                                                    }
                                                                                }
                                                                                __state_exit_partial_reduction_inner_7_sdfg:;
                                                                            }    ///////////////////

                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_7_red_reduceTile:
                                                            {
                                                                {
                                                                    for (int k = 0; k < 16; k += 1) {
                                                                        #pragma HLS PIPELINE II=1
                                                                        #pragma HLS LOOP_FLATTEN
                                                                        {
                                                                            auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (red_buf + k);
                                                                            dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (res_buf);
                                                                            dace::vec<float, 1> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (finalReduction)
                                                                            outCon = inCon;
                                                                            ////////////////////

                                                                            __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            __state_redTile_sdfg_7_store_reduceTile:
                                                            {
                                                                {
                                                                    auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (res_buf);
                                                                    dace::vec<float, 1> inCon = __inCon.val<1>();

                                                                    auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (_y_red + ii);
                                                                    dace::vec<float, 1> outCon;

                                                                    ////////////////////
                                                                    // Tasklet code (storeRed_task)
                                                                    outCon = inCon;
                                                                    ////////////////////

                                                                    __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                                                }
                                                            }
                                                            if ((j == ((n / 8192) - 1))) {
                                                                __state_redTile_sdfg_7_write_y_reduceTile:
                                                                {
                                                                    _res_red.push(dace::Read<float, 1>(_y_red + ii));
                                                                    #pragma HLS DEPENDENCE variable=_y_red false
                                                                }
                                                                __state_exit_redTile_sdfg_7_store_reduceTile_then:;
                                                                } else {
                                                                __state_redTile_sdfg_7_write_empty_reduceTile:
                                                                ;
                                                                __state_exit_redTile_sdfg_7_store_reduceTile_else:;
                                                            }
                                                            __state_redTile_sdfg_7_end_reduceTile:
                                                            ;
                                                            __state_exit_redTile_sdfg_7_sdfg:;
                                                        }    ///////////////////

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                __state_exit_yTile_sdfg_7_sdfg:;
                            }    ///////////////////

                        }
                    }
                }
            }
            __state_exit_gemv_fpga_stream_rowTiles_7_sdfg:;
        }    ///////////////////

    }
}

void module_saxpy_l2_4(dace::FIFO<float, 1, 32> &_res_to_saxpy_l1_2_y_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_4_x_0, dace::FIFO<float, 1, 32> &_res_to_saxpy_l2_4_y_0, float a, int n) {
    {
        auto ___y = dace::make_streamview(_res_to_saxpy_l2_4_y_0);
        auto &_y = ___y;
        auto ___x = dace::make_streamview(_res_to_saxpy_l2_4_x_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(_res_to_saxpy_l1_2_y_0);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_vecAdd_graph_4_state_0:
            {
                {
                    for (int i = 0; i < n; i += 1) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS LOOP_FLATTEN
                        {
                            auto __x_con = _x;
                            auto x_con = __x_con.pop();
                            auto __y_con = _y;
                            auto y_con = __y_con.pop();

                            auto __z_con = _res;
                            dace::vec<float, 1> z_con;

                            ////////////////////
                            // Tasklet code (vecAdd_task)
                            z_con = ((a * x_con) + y_con);
                            ////////////////////

                            __z_con.write(z_con);
                        }
                    }
                }
            }
            __state_exit_vecAdd_graph_4_sdfg:;
        }    ///////////////////

    }
}

void module_blas_asum(dace::FIFO<float, 1, 32> &_res_to_blas_asum_x_0, dace::FIFO<float, 1, 32> &fpga_res__res_wS, float a, int n) {
    {
        auto ___x = dace::make_streamview(_res_to_blas_asum_x_0);
        auto &_x = ___x;
        auto ___res = dace::make_streamview(fpga_res__res_wS);
        auto &_res = ___res;

        {    ///////////////////
            int __dacesym_n = n;
            auto n = __dacesym_n;
            dace::vec<float, 1> red_buf[16];
            dace::vec<float, 1> res_buf[1];
            #pragma HLS ARRAY_PARTITION variable=res_buf complete

            __state_asum_fpga_linearReduction_init_state:
            {
                {
                    for (int j_init = 0; j_init < 16; j_init += 1) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS LOOP_FLATTEN
                        {

                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (red_buf + j_init);
                            dace::vec<float, 1> out;

                            ////////////////////
                            // Tasklet code (init_red_buf)
                            out = 0;
                            ////////////////////

                            __out.write(out);
                            #pragma HLS DEPENDENCE variable=out false
                        }
                    }
                }
                {
                    {
                        const int j_init = 0; // Degenerate loop
                        {

                            auto __out = dace::ArrayViewOut<float, 0, 1, 1> (res_buf + j_init);
                            dace::vec<float, 1> out;

                            ////////////////////
                            // Tasklet code (init_res_buf)
                            out = 0;
                            ////////////////////

                            __out.write(out);
                            #pragma HLS DEPENDENCE variable=out false
                        }
                    }
                }
            }
            __state_asum_fpga_linearReduction_abs_state:
            {
                {
                    for (int i = 0; i < n; i += 1) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS LOOP_FLATTEN
                        {
                            auto __inner_x = _x;
                            auto &inner_x = __inner_x;
                            auto __partial_out = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (red_buf, 1);
                            auto *partial_out = __partial_out.ptr<1>();

                            {    ///////////////////
                                int __dacesym_i = i;
                                auto i = __dacesym_i;
                                dace::vec<float, 1> buf_x[1];
                                dace::vec<float, 1> reg_buf[1];
                                #pragma HLS ARRAY_PARTITION variable=reg_buf complete

                                __state_partial_reduction_inner_init_state:
                                {
                                    dace::Write<float, 1>(buf_x, dace::Read<float, 1>(inner_x.pop()));
                                    #pragma HLS DEPENDENCE variable=buf_x false
                                    {
                                        {
                                            const int j_init = 0; // Degenerate loop
                                            {

                                                auto __out = dace::ArrayViewOut<float, 0, 1, 1> (reg_buf + j_init);
                                                dace::vec<float, 1> out;

                                                ////////////////////
                                                // Tasklet code (init_reg_buf)
                                                out = 0;
                                                ////////////////////

                                                __out.write(out);
                                                #pragma HLS DEPENDENCE variable=out false
                                            }
                                        }
                                    }
                                }
                                __state_partial_reduction_inner_compute_state:
                                {
                                    {
                                        {
                                            const int j = 0; // Degenerate loop
                                            {
                                                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (buf_x + j);
                                                dace::vec<float, 1> inCon = __inCon.val<1>();

                                                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (reg_buf);
                                                dace::vec<float, 1> outCon;

                                                ////////////////////
                                                // Tasklet code (compRed_task)
                                                outCon = fabs(inCon);
                                                ////////////////////

                                                __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                                            }
                                        }
                                    }
                                }
                                __state_partial_reduction_inner_store_state:
                                {
                                    {
                                        auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (reg_buf);
                                        dace::vec<float, 1> inCon = __inCon.val<1>();
                                        auto __prevCon = dace::ArrayViewIn<float, 0, 1, 1> (partial_out + (i % 16));
                                        dace::vec<float, 1> prevCon = __prevCon.val<1>();

                                        auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (partial_out + (i % 16));
                                        dace::vec<float, 1> outCon;

                                        ////////////////////
                                        // Tasklet code (store_out_task)
                                        outCon = (inCon + prevCon);
                                        ////////////////////

                                        __outCon.write(outCon);
                                        #pragma HLS DEPENDENCE variable=outCon false
                                    }
                                }
                                __state_exit_partial_reduction_inner_sdfg:;
                            }    ///////////////////

                        }
                    }
                }
            }
            __state_asum_fpga_linearReduction_reduction_state:
            {
                {
                    for (int i = 0; i < 16; i += 1) {
                        #pragma HLS UNROLL
                        {
                            auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (red_buf + i);
                            dace::vec<float, 1> inCon = __inCon.val<1>();

                            auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (res_buf);
                            dace::vec<float, 1> outCon;

                            ////////////////////
                            // Tasklet code (reduce_task)
                            outCon = inCon;
                            ////////////////////

                            __outCon.write_and_resolve<dace::ReductionType::Sum>(outCon);
                        }
                    }
                }
            }
            __state_asum_fpga_linearReduction_final_state:
            {
                {
                    auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (res_buf);
                    dace::vec<float, 1> inCon = __inCon.val<1>();

                    auto __outCon = _res;
                    auto &outCon = __outCon;

                    ////////////////////
                    // Tasklet code (mapToStream_task)
                    __outCon.write(inCon);
                    ////////////////////

                }
            }
            __state_exit_asum_fpga_linearReduction_sdfg:;
        }    ///////////////////

    }
}

void module_sR_f_A_ger__fk_rS(dace::vec<float, 16> const *f_A_ger_in, dace::FIFO<float, 16, 32> &f_A_ger__fk_rS, float a, int n) {

    dace::ArrayInterface<float, 16> f_A_ger(f_A_ger_in, nullptr);

    {
        for (int i = 0; i < (n / 8192); i += 1) {
            {
                for (int j = 0; j < (n / 8192); j += 1) {
                    {
                        for (int ii = 0; ii < 8192; ii += 1) {
                            {
                                for (int jj = 0; jj < 512; jj += 1) {
                                    #pragma HLS PIPELINE II=1
                                    #pragma HLS LOOP_FLATTEN
                                    {
                                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (f_A_ger + (((512 * j) + jj) + ((n * ((8192 * i) + ii)) / 16)));
                                        dace::vec<float, 16> inCon = __inCon.val<16>();

                                        auto __outCon = dace::make_streamview(f_A_ger__fk_rS);
                                        dace::vec<float, 16> outCon;

                                        ////////////////////
                                        // Tasklet code (sR_f_A_ger__fk_rS)
                                        outCon = inCon;
                                        ////////////////////

                                        __outCon.write(outCon);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void module_GER1(dace::FIFO<float, 16, 32> &_RES_to_GEMV1_A_0, dace::FIFO<float, 16, 32> &f_A_ger_GER1_0, dace::FIFO<float, 16, 32> &f_x_ger_GER1_0, dace::FIFO<float, 1, 32> &f_y1_ger__y_rS, float a, int n) {
    {
        auto ___A = dace::make_streamview(f_A_ger_GER1_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_ger_GER1_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(f_y1_ger__y_rS);
        auto &_y = ___y;
        auto ___RES = dace::make_streamview(_RES_to_GEMV1_A_0);
        auto &_RES = ___RES;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_ger_fpga_stream_rowTiles_1_ger_compute:
            {
                dace::vec<float, 1> y_buf_row[8192];
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            for (int j = 0; j < (n / 8192); j += 1) {
                                {
                                    for (int ii = 0; ii < 8192; ii += 1) {
                                        {
                                            auto ___A_tile = _A;
                                            auto &_A_tile = ___A_tile;
                                            auto ___x_tile = _x;
                                            auto &_x_tile = ___x_tile;
                                            auto ___y_tile = _y;
                                            auto &_y_tile = ___y_tile;
                                            auto ___A_out_tile = _RES;
                                            auto &_A_out_tile = ___A_out_tile;
                                            auto ___y_buf_tile = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_buf_row, 1);
                                            auto *_y_buf_tile = ___y_buf_tile.ptr<1>();

                                            {    ///////////////////
                                                int __dacesym_a = a;
                                                int __dacesym_ii = ii;
                                                int __dacesym_j = j;
                                                int __dacesym_n = n;
                                                auto a = __dacesym_a;
                                                auto ii = __dacesym_ii;
                                                auto j = __dacesym_j;
                                                auto n = __dacesym_n;

                                                __state_tile_sdfg_1_init_state_tile:
                                                ;
                                                if ((j == 0)) {
                                                    __state_tile_sdfg_1_read_y_reduceTile:
                                                    {
                                                        dace::vec<float, 1> y_buf[1];
                                                        #pragma HLS ARRAY_PARTITION variable=y_buf complete
                                                        dace::Write<float, 1>(y_buf, dace::Read<float, 1>(_y_tile.pop()));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        dace::Write<float, 1>(_y_buf_tile + ii, dace::Read<float, 1>(y_buf));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        #pragma HLS DEPENDENCE variable=_y_buf_tile false
                                                    }
                                                    __state_exit_tile_sdfg_1_init_state_tile_then:;
                                                    } else {
                                                    __state_tile_sdfg_1_read_empty_reduceTile:
                                                    ;
                                                    __state_exit_tile_sdfg_1_init_state_tile_else:;
                                                }
                                                __state_tile_sdfg_1_copmute_state_tile:
                                                {
                                                    dace::vec<float, 16> x_buf[(8192 / 16)];
                                                    {
                                                        for (int jj = 0; jj < 512; jj += 1) {
                                                            #pragma HLS PIPELINE II=1
                                                            #pragma HLS LOOP_FLATTEN
                                                            {
                                                                auto ___A_unroll = _A_tile;
                                                                auto &_A_unroll = ___A_unroll;
                                                                auto ___x_unroll = _x_tile;
                                                                auto &_x_unroll = ___x_unroll;
                                                                auto ___y_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (_y_buf_tile, 1);
                                                                auto *_y_unroll = ___y_unroll.ptr<1>();
                                                                auto ___A_out_unroll = _A_out_tile;
                                                                auto &_A_out_unroll = ___A_out_unroll;
                                                                auto ___x_buf_unroll = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                auto *_x_buf_unroll = ___x_buf_unroll.ptr<16>();

                                                                {    ///////////////////
                                                                    int __dacesym_a = a;
                                                                    int __dacesym_ii = ii;
                                                                    int __dacesym_jj = jj;
                                                                    auto a = __dacesym_a;
                                                                    auto ii = __dacesym_ii;
                                                                    auto jj = __dacesym_jj;
                                                                    dace::vec<float, 16> A_out_buf;

                                                                    __state_vectorize_inner_graph_1_init_state:
                                                                    ;
                                                                    if ((ii == 0)) {
                                                                        __state_vectorize_inner_graph_1_readX_state:
                                                                        {
                                                                            {
                                                                                auto __inCon = _x_unroll;
                                                                                auto inCon = __inCon.pop();

                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                                dace::vec<float, 16> outCon;

                                                                                ////////////////////
                                                                                // Tasklet code (streamToLocal_map)
                                                                                outCon = inCon;
                                                                                ////////////////////

                                                                                __outCon.write(outCon);
                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                            }
                                                                        }
                                                                        __state_exit_vectorize_inner_graph_1_init_state_then:;
                                                                        } else {
                                                                        __state_vectorize_inner_graph_1_readEmpty_state:
                                                                        ;
                                                                        __state_exit_vectorize_inner_graph_1_init_state_else:;
                                                                    }
                                                                    __state_vectorize_inner_graph_1_compute_state:
                                                                    {
                                                                        {
                                                                            auto __A_con = _A_unroll;
                                                                            auto A_con = __A_con.pop();
                                                                            auto __x_con = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                            dace::vec<float, 16> x_con = __x_con.val<16>();
                                                                            auto __y_con = dace::ArrayViewIn<float, 0, 1, 1> (_y_unroll + ii);
                                                                            dace::vec<float, 1> y_con = __y_con.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&A_out_buf);
                                                                            dace::vec<float, 16> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (compute_task)
                                                                            outCon = (A_con + ((x_con * y_con) * a));
                                                                            ////////////////////

                                                                            __outCon.write(outCon);
                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                        }
                                                                    }
                                                                    __state_vectorize_inner_graph_1_streamOut_state:
                                                                    {
                                                                        _A_out_unroll.push(dace::Read<float, 16>(A_out_buf));
                                                                        #pragma HLS DEPENDENCE variable=A_out_buf false
                                                                    }
                                                                    __state_exit_vectorize_inner_graph_1_sdfg:;
                                                                }    ///////////////////

                                                            }
                                                        }
                                                    }
                                                }
                                                __state_exit_tile_sdfg_1_sdfg:;
                                            }    ///////////////////

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            __state_exit_ger_fpga_stream_rowTiles_1_sdfg:;
        }    ///////////////////

    }
}

void module_GER2(dace::FIFO<float, 16, 32> &_RES_to_GEMV2_A_0, dace::FIFO<float, 16, 32> &f_A_ger_GER2_0, dace::FIFO<float, 16, 32> &f_x_ger_GER2_0, dace::FIFO<float, 1, 32> &f_y2_ger__y_rS, float a, int n) {
    {
        auto ___A = dace::make_streamview(f_A_ger_GER2_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_ger_GER2_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(f_y2_ger__y_rS);
        auto &_y = ___y;
        auto ___RES = dace::make_streamview(_RES_to_GEMV2_A_0);
        auto &_RES = ___RES;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_ger_fpga_stream_rowTiles_2_ger_compute:
            {
                dace::vec<float, 1> y_buf_row[8192];
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            for (int j = 0; j < (n / 8192); j += 1) {
                                {
                                    for (int ii = 0; ii < 8192; ii += 1) {
                                        {
                                            auto ___A_tile = _A;
                                            auto &_A_tile = ___A_tile;
                                            auto ___x_tile = _x;
                                            auto &_x_tile = ___x_tile;
                                            auto ___y_tile = _y;
                                            auto &_y_tile = ___y_tile;
                                            auto ___A_out_tile = _RES;
                                            auto &_A_out_tile = ___A_out_tile;
                                            auto ___y_buf_tile = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_buf_row, 1);
                                            auto *_y_buf_tile = ___y_buf_tile.ptr<1>();

                                            {    ///////////////////
                                                int __dacesym_a = a;
                                                int __dacesym_ii = ii;
                                                int __dacesym_j = j;
                                                int __dacesym_n = n;
                                                auto a = __dacesym_a;
                                                auto ii = __dacesym_ii;
                                                auto j = __dacesym_j;
                                                auto n = __dacesym_n;

                                                __state_tile_sdfg_2_init_state_tile:
                                                ;
                                                if ((j == 0)) {
                                                    __state_tile_sdfg_2_read_y_reduceTile:
                                                    {
                                                        dace::vec<float, 1> y_buf[1];
                                                        #pragma HLS ARRAY_PARTITION variable=y_buf complete
                                                        dace::Write<float, 1>(y_buf, dace::Read<float, 1>(_y_tile.pop()));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        dace::Write<float, 1>(_y_buf_tile + ii, dace::Read<float, 1>(y_buf));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        #pragma HLS DEPENDENCE variable=_y_buf_tile false
                                                    }
                                                    __state_exit_tile_sdfg_2_init_state_tile_then:;
                                                    } else {
                                                    __state_tile_sdfg_2_read_empty_reduceTile:
                                                    ;
                                                    __state_exit_tile_sdfg_2_init_state_tile_else:;
                                                }
                                                __state_tile_sdfg_2_copmute_state_tile:
                                                {
                                                    dace::vec<float, 16> x_buf[(8192 / 16)];
                                                    {
                                                        for (int jj = 0; jj < 512; jj += 1) {
                                                            #pragma HLS PIPELINE II=1
                                                            #pragma HLS LOOP_FLATTEN
                                                            {
                                                                auto ___A_unroll = _A_tile;
                                                                auto &_A_unroll = ___A_unroll;
                                                                auto ___x_unroll = _x_tile;
                                                                auto &_x_unroll = ___x_unroll;
                                                                auto ___y_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (_y_buf_tile, 1);
                                                                auto *_y_unroll = ___y_unroll.ptr<1>();
                                                                auto ___A_out_unroll = _A_out_tile;
                                                                auto &_A_out_unroll = ___A_out_unroll;
                                                                auto ___x_buf_unroll = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                auto *_x_buf_unroll = ___x_buf_unroll.ptr<16>();

                                                                {    ///////////////////
                                                                    int __dacesym_a = a;
                                                                    int __dacesym_ii = ii;
                                                                    int __dacesym_jj = jj;
                                                                    auto a = __dacesym_a;
                                                                    auto ii = __dacesym_ii;
                                                                    auto jj = __dacesym_jj;
                                                                    dace::vec<float, 16> A_out_buf;

                                                                    __state_vectorize_inner_graph_2_init_state:
                                                                    ;
                                                                    if ((ii == 0)) {
                                                                        __state_vectorize_inner_graph_2_readX_state:
                                                                        {
                                                                            {
                                                                                auto __inCon = _x_unroll;
                                                                                auto inCon = __inCon.pop();

                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                                dace::vec<float, 16> outCon;

                                                                                ////////////////////
                                                                                // Tasklet code (streamToLocal_map)
                                                                                outCon = inCon;
                                                                                ////////////////////

                                                                                __outCon.write(outCon);
                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                            }
                                                                        }
                                                                        __state_exit_vectorize_inner_graph_2_init_state_then:;
                                                                        } else {
                                                                        __state_vectorize_inner_graph_2_readEmpty_state:
                                                                        ;
                                                                        __state_exit_vectorize_inner_graph_2_init_state_else:;
                                                                    }
                                                                    __state_vectorize_inner_graph_2_compute_state:
                                                                    {
                                                                        {
                                                                            auto __A_con = _A_unroll;
                                                                            auto A_con = __A_con.pop();
                                                                            auto __x_con = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                            dace::vec<float, 16> x_con = __x_con.val<16>();
                                                                            auto __y_con = dace::ArrayViewIn<float, 0, 1, 1> (_y_unroll + ii);
                                                                            dace::vec<float, 1> y_con = __y_con.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&A_out_buf);
                                                                            dace::vec<float, 16> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (compute_task)
                                                                            outCon = (A_con + ((x_con * y_con) * a));
                                                                            ////////////////////

                                                                            __outCon.write(outCon);
                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                        }
                                                                    }
                                                                    __state_vectorize_inner_graph_2_streamOut_state:
                                                                    {
                                                                        _A_out_unroll.push(dace::Read<float, 16>(A_out_buf));
                                                                        #pragma HLS DEPENDENCE variable=A_out_buf false
                                                                    }
                                                                    __state_exit_vectorize_inner_graph_2_sdfg:;
                                                                }    ///////////////////

                                                            }
                                                        }
                                                    }
                                                }
                                                __state_exit_tile_sdfg_2_sdfg:;
                                            }    ///////////////////

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            __state_exit_ger_fpga_stream_rowTiles_2_sdfg:;
        }    ///////////////////

    }
}

void module_GER3(dace::FIFO<float, 16, 32> &_RES_to_GEMV3_A_0, dace::FIFO<float, 16, 32> &f_A_ger_GER3_0, dace::FIFO<float, 16, 32> &f_x_ger_GER3_0, dace::FIFO<float, 1, 32> &f_y3_ger__y_rS, float a, int n) {
    {
        auto ___A = dace::make_streamview(f_A_ger_GER3_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_ger_GER3_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(f_y3_ger__y_rS);
        auto &_y = ___y;
        auto ___RES = dace::make_streamview(_RES_to_GEMV3_A_0);
        auto &_RES = ___RES;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_ger_fpga_stream_rowTiles_3_ger_compute:
            {
                dace::vec<float, 1> y_buf_row[8192];
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            for (int j = 0; j < (n / 8192); j += 1) {
                                {
                                    for (int ii = 0; ii < 8192; ii += 1) {
                                        {
                                            auto ___A_tile = _A;
                                            auto &_A_tile = ___A_tile;
                                            auto ___x_tile = _x;
                                            auto &_x_tile = ___x_tile;
                                            auto ___y_tile = _y;
                                            auto &_y_tile = ___y_tile;
                                            auto ___A_out_tile = _RES;
                                            auto &_A_out_tile = ___A_out_tile;
                                            auto ___y_buf_tile = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_buf_row, 1);
                                            auto *_y_buf_tile = ___y_buf_tile.ptr<1>();

                                            {    ///////////////////
                                                int __dacesym_a = a;
                                                int __dacesym_ii = ii;
                                                int __dacesym_j = j;
                                                int __dacesym_n = n;
                                                auto a = __dacesym_a;
                                                auto ii = __dacesym_ii;
                                                auto j = __dacesym_j;
                                                auto n = __dacesym_n;

                                                __state_tile_sdfg_3_init_state_tile:
                                                ;
                                                if ((j == 0)) {
                                                    __state_tile_sdfg_3_read_y_reduceTile:
                                                    {
                                                        dace::vec<float, 1> y_buf[1];
                                                        #pragma HLS ARRAY_PARTITION variable=y_buf complete
                                                        dace::Write<float, 1>(y_buf, dace::Read<float, 1>(_y_tile.pop()));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        dace::Write<float, 1>(_y_buf_tile + ii, dace::Read<float, 1>(y_buf));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        #pragma HLS DEPENDENCE variable=_y_buf_tile false
                                                    }
                                                    __state_exit_tile_sdfg_3_init_state_tile_then:;
                                                    } else {
                                                    __state_tile_sdfg_3_read_empty_reduceTile:
                                                    ;
                                                    __state_exit_tile_sdfg_3_init_state_tile_else:;
                                                }
                                                __state_tile_sdfg_3_copmute_state_tile:
                                                {
                                                    dace::vec<float, 16> x_buf[(8192 / 16)];
                                                    {
                                                        for (int jj = 0; jj < 512; jj += 1) {
                                                            #pragma HLS PIPELINE II=1
                                                            #pragma HLS LOOP_FLATTEN
                                                            {
                                                                auto ___A_unroll = _A_tile;
                                                                auto &_A_unroll = ___A_unroll;
                                                                auto ___x_unroll = _x_tile;
                                                                auto &_x_unroll = ___x_unroll;
                                                                auto ___y_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (_y_buf_tile, 1);
                                                                auto *_y_unroll = ___y_unroll.ptr<1>();
                                                                auto ___A_out_unroll = _A_out_tile;
                                                                auto &_A_out_unroll = ___A_out_unroll;
                                                                auto ___x_buf_unroll = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                auto *_x_buf_unroll = ___x_buf_unroll.ptr<16>();

                                                                {    ///////////////////
                                                                    int __dacesym_a = a;
                                                                    int __dacesym_ii = ii;
                                                                    int __dacesym_jj = jj;
                                                                    auto a = __dacesym_a;
                                                                    auto ii = __dacesym_ii;
                                                                    auto jj = __dacesym_jj;
                                                                    dace::vec<float, 16> A_out_buf;

                                                                    __state_vectorize_inner_graph_3_init_state:
                                                                    ;
                                                                    if ((ii == 0)) {
                                                                        __state_vectorize_inner_graph_3_readX_state:
                                                                        {
                                                                            {
                                                                                auto __inCon = _x_unroll;
                                                                                auto inCon = __inCon.pop();

                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                                dace::vec<float, 16> outCon;

                                                                                ////////////////////
                                                                                // Tasklet code (streamToLocal_map)
                                                                                outCon = inCon;
                                                                                ////////////////////

                                                                                __outCon.write(outCon);
                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                            }
                                                                        }
                                                                        __state_exit_vectorize_inner_graph_3_init_state_then:;
                                                                        } else {
                                                                        __state_vectorize_inner_graph_3_readEmpty_state:
                                                                        ;
                                                                        __state_exit_vectorize_inner_graph_3_init_state_else:;
                                                                    }
                                                                    __state_vectorize_inner_graph_3_compute_state:
                                                                    {
                                                                        {
                                                                            auto __A_con = _A_unroll;
                                                                            auto A_con = __A_con.pop();
                                                                            auto __x_con = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                            dace::vec<float, 16> x_con = __x_con.val<16>();
                                                                            auto __y_con = dace::ArrayViewIn<float, 0, 1, 1> (_y_unroll + ii);
                                                                            dace::vec<float, 1> y_con = __y_con.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&A_out_buf);
                                                                            dace::vec<float, 16> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (compute_task)
                                                                            outCon = (A_con + ((x_con * y_con) * a));
                                                                            ////////////////////

                                                                            __outCon.write(outCon);
                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                        }
                                                                    }
                                                                    __state_vectorize_inner_graph_3_streamOut_state:
                                                                    {
                                                                        _A_out_unroll.push(dace::Read<float, 16>(A_out_buf));
                                                                        #pragma HLS DEPENDENCE variable=A_out_buf false
                                                                    }
                                                                    __state_exit_vectorize_inner_graph_3_sdfg:;
                                                                }    ///////////////////

                                                            }
                                                        }
                                                    }
                                                }
                                                __state_exit_tile_sdfg_3_sdfg:;
                                            }    ///////////////////

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            __state_exit_ger_fpga_stream_rowTiles_3_sdfg:;
        }    ///////////////////

    }
}

void module_GER4(dace::FIFO<float, 16, 32> &_RES_to_GEMV4_A_0, dace::FIFO<float, 16, 32> &f_A_ger_GER4_0, dace::FIFO<float, 16, 32> &f_x_ger_GER4_0, dace::FIFO<float, 1, 32> &f_y4_ger__y_rS, float a, int n) {
    {
        auto ___A = dace::make_streamview(f_A_ger_GER4_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_ger_GER4_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(f_y4_ger__y_rS);
        auto &_y = ___y;
        auto ___RES = dace::make_streamview(_RES_to_GEMV4_A_0);
        auto &_RES = ___RES;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_ger_fpga_stream_rowTiles_4_ger_compute:
            {
                dace::vec<float, 1> y_buf_row[8192];
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            for (int j = 0; j < (n / 8192); j += 1) {
                                {
                                    for (int ii = 0; ii < 8192; ii += 1) {
                                        {
                                            auto ___A_tile = _A;
                                            auto &_A_tile = ___A_tile;
                                            auto ___x_tile = _x;
                                            auto &_x_tile = ___x_tile;
                                            auto ___y_tile = _y;
                                            auto &_y_tile = ___y_tile;
                                            auto ___A_out_tile = _RES;
                                            auto &_A_out_tile = ___A_out_tile;
                                            auto ___y_buf_tile = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_buf_row, 1);
                                            auto *_y_buf_tile = ___y_buf_tile.ptr<1>();

                                            {    ///////////////////
                                                int __dacesym_a = a;
                                                int __dacesym_ii = ii;
                                                int __dacesym_j = j;
                                                int __dacesym_n = n;
                                                auto a = __dacesym_a;
                                                auto ii = __dacesym_ii;
                                                auto j = __dacesym_j;
                                                auto n = __dacesym_n;

                                                __state_tile_sdfg_4_init_state_tile:
                                                ;
                                                if ((j == 0)) {
                                                    __state_tile_sdfg_4_read_y_reduceTile:
                                                    {
                                                        dace::vec<float, 1> y_buf[1];
                                                        #pragma HLS ARRAY_PARTITION variable=y_buf complete
                                                        dace::Write<float, 1>(y_buf, dace::Read<float, 1>(_y_tile.pop()));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        dace::Write<float, 1>(_y_buf_tile + ii, dace::Read<float, 1>(y_buf));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        #pragma HLS DEPENDENCE variable=_y_buf_tile false
                                                    }
                                                    __state_exit_tile_sdfg_4_init_state_tile_then:;
                                                    } else {
                                                    __state_tile_sdfg_4_read_empty_reduceTile:
                                                    ;
                                                    __state_exit_tile_sdfg_4_init_state_tile_else:;
                                                }
                                                __state_tile_sdfg_4_copmute_state_tile:
                                                {
                                                    dace::vec<float, 16> x_buf[(8192 / 16)];
                                                    {
                                                        for (int jj = 0; jj < 512; jj += 1) {
                                                            #pragma HLS PIPELINE II=1
                                                            #pragma HLS LOOP_FLATTEN
                                                            {
                                                                auto ___A_unroll = _A_tile;
                                                                auto &_A_unroll = ___A_unroll;
                                                                auto ___x_unroll = _x_tile;
                                                                auto &_x_unroll = ___x_unroll;
                                                                auto ___y_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (_y_buf_tile, 1);
                                                                auto *_y_unroll = ___y_unroll.ptr<1>();
                                                                auto ___A_out_unroll = _A_out_tile;
                                                                auto &_A_out_unroll = ___A_out_unroll;
                                                                auto ___x_buf_unroll = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                auto *_x_buf_unroll = ___x_buf_unroll.ptr<16>();

                                                                {    ///////////////////
                                                                    int __dacesym_a = a;
                                                                    int __dacesym_ii = ii;
                                                                    int __dacesym_jj = jj;
                                                                    auto a = __dacesym_a;
                                                                    auto ii = __dacesym_ii;
                                                                    auto jj = __dacesym_jj;
                                                                    dace::vec<float, 16> A_out_buf;

                                                                    __state_vectorize_inner_graph_4_init_state:
                                                                    ;
                                                                    if ((ii == 0)) {
                                                                        __state_vectorize_inner_graph_4_readX_state:
                                                                        {
                                                                            {
                                                                                auto __inCon = _x_unroll;
                                                                                auto inCon = __inCon.pop();

                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                                dace::vec<float, 16> outCon;

                                                                                ////////////////////
                                                                                // Tasklet code (streamToLocal_map)
                                                                                outCon = inCon;
                                                                                ////////////////////

                                                                                __outCon.write(outCon);
                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                            }
                                                                        }
                                                                        __state_exit_vectorize_inner_graph_4_init_state_then:;
                                                                        } else {
                                                                        __state_vectorize_inner_graph_4_readEmpty_state:
                                                                        ;
                                                                        __state_exit_vectorize_inner_graph_4_init_state_else:;
                                                                    }
                                                                    __state_vectorize_inner_graph_4_compute_state:
                                                                    {
                                                                        {
                                                                            auto __A_con = _A_unroll;
                                                                            auto A_con = __A_con.pop();
                                                                            auto __x_con = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                            dace::vec<float, 16> x_con = __x_con.val<16>();
                                                                            auto __y_con = dace::ArrayViewIn<float, 0, 1, 1> (_y_unroll + ii);
                                                                            dace::vec<float, 1> y_con = __y_con.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&A_out_buf);
                                                                            dace::vec<float, 16> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (compute_task)
                                                                            outCon = (A_con + ((x_con * y_con) * a));
                                                                            ////////////////////

                                                                            __outCon.write(outCon);
                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                        }
                                                                    }
                                                                    __state_vectorize_inner_graph_4_streamOut_state:
                                                                    {
                                                                        _A_out_unroll.push(dace::Read<float, 16>(A_out_buf));
                                                                        #pragma HLS DEPENDENCE variable=A_out_buf false
                                                                    }
                                                                    __state_exit_vectorize_inner_graph_4_sdfg:;
                                                                }    ///////////////////

                                                            }
                                                        }
                                                    }
                                                }
                                                __state_exit_tile_sdfg_4_sdfg:;
                                            }    ///////////////////

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            __state_exit_ger_fpga_stream_rowTiles_4_sdfg:;
        }    ///////////////////

    }
}

void module_GER5(dace::FIFO<float, 16, 32> &_RES_to_GEMV5_A_0, dace::FIFO<float, 16, 32> &f_A_ger_GER5_0, dace::FIFO<float, 16, 32> &f_x_ger_GER5_0, dace::FIFO<float, 1, 32> &f_y5_ger__y_rS, float a, int n) {
    {
        auto ___A = dace::make_streamview(f_A_ger_GER5_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_ger_GER5_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(f_y5_ger__y_rS);
        auto &_y = ___y;
        auto ___RES = dace::make_streamview(_RES_to_GEMV5_A_0);
        auto &_RES = ___RES;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_ger_fpga_stream_rowTiles_5_ger_compute:
            {
                dace::vec<float, 1> y_buf_row[8192];
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            for (int j = 0; j < (n / 8192); j += 1) {
                                {
                                    for (int ii = 0; ii < 8192; ii += 1) {
                                        {
                                            auto ___A_tile = _A;
                                            auto &_A_tile = ___A_tile;
                                            auto ___x_tile = _x;
                                            auto &_x_tile = ___x_tile;
                                            auto ___y_tile = _y;
                                            auto &_y_tile = ___y_tile;
                                            auto ___A_out_tile = _RES;
                                            auto &_A_out_tile = ___A_out_tile;
                                            auto ___y_buf_tile = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_buf_row, 1);
                                            auto *_y_buf_tile = ___y_buf_tile.ptr<1>();

                                            {    ///////////////////
                                                int __dacesym_a = a;
                                                int __dacesym_ii = ii;
                                                int __dacesym_j = j;
                                                int __dacesym_n = n;
                                                auto a = __dacesym_a;
                                                auto ii = __dacesym_ii;
                                                auto j = __dacesym_j;
                                                auto n = __dacesym_n;

                                                __state_tile_sdfg_5_init_state_tile:
                                                ;
                                                if ((j == 0)) {
                                                    __state_tile_sdfg_5_read_y_reduceTile:
                                                    {
                                                        dace::vec<float, 1> y_buf[1];
                                                        #pragma HLS ARRAY_PARTITION variable=y_buf complete
                                                        dace::Write<float, 1>(y_buf, dace::Read<float, 1>(_y_tile.pop()));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        dace::Write<float, 1>(_y_buf_tile + ii, dace::Read<float, 1>(y_buf));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        #pragma HLS DEPENDENCE variable=_y_buf_tile false
                                                    }
                                                    __state_exit_tile_sdfg_5_init_state_tile_then:;
                                                    } else {
                                                    __state_tile_sdfg_5_read_empty_reduceTile:
                                                    ;
                                                    __state_exit_tile_sdfg_5_init_state_tile_else:;
                                                }
                                                __state_tile_sdfg_5_copmute_state_tile:
                                                {
                                                    dace::vec<float, 16> x_buf[(8192 / 16)];
                                                    {
                                                        for (int jj = 0; jj < 512; jj += 1) {
                                                            #pragma HLS PIPELINE II=1
                                                            #pragma HLS LOOP_FLATTEN
                                                            {
                                                                auto ___A_unroll = _A_tile;
                                                                auto &_A_unroll = ___A_unroll;
                                                                auto ___x_unroll = _x_tile;
                                                                auto &_x_unroll = ___x_unroll;
                                                                auto ___y_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (_y_buf_tile, 1);
                                                                auto *_y_unroll = ___y_unroll.ptr<1>();
                                                                auto ___A_out_unroll = _A_out_tile;
                                                                auto &_A_out_unroll = ___A_out_unroll;
                                                                auto ___x_buf_unroll = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                auto *_x_buf_unroll = ___x_buf_unroll.ptr<16>();

                                                                {    ///////////////////
                                                                    int __dacesym_a = a;
                                                                    int __dacesym_ii = ii;
                                                                    int __dacesym_jj = jj;
                                                                    auto a = __dacesym_a;
                                                                    auto ii = __dacesym_ii;
                                                                    auto jj = __dacesym_jj;
                                                                    dace::vec<float, 16> A_out_buf;

                                                                    __state_vectorize_inner_graph_5_init_state:
                                                                    ;
                                                                    if ((ii == 0)) {
                                                                        __state_vectorize_inner_graph_5_readX_state:
                                                                        {
                                                                            {
                                                                                auto __inCon = _x_unroll;
                                                                                auto inCon = __inCon.pop();

                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                                dace::vec<float, 16> outCon;

                                                                                ////////////////////
                                                                                // Tasklet code (streamToLocal_map)
                                                                                outCon = inCon;
                                                                                ////////////////////

                                                                                __outCon.write(outCon);
                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                            }
                                                                        }
                                                                        __state_exit_vectorize_inner_graph_5_init_state_then:;
                                                                        } else {
                                                                        __state_vectorize_inner_graph_5_readEmpty_state:
                                                                        ;
                                                                        __state_exit_vectorize_inner_graph_5_init_state_else:;
                                                                    }
                                                                    __state_vectorize_inner_graph_5_compute_state:
                                                                    {
                                                                        {
                                                                            auto __A_con = _A_unroll;
                                                                            auto A_con = __A_con.pop();
                                                                            auto __x_con = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                            dace::vec<float, 16> x_con = __x_con.val<16>();
                                                                            auto __y_con = dace::ArrayViewIn<float, 0, 1, 1> (_y_unroll + ii);
                                                                            dace::vec<float, 1> y_con = __y_con.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&A_out_buf);
                                                                            dace::vec<float, 16> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (compute_task)
                                                                            outCon = (A_con + ((x_con * y_con) * a));
                                                                            ////////////////////

                                                                            __outCon.write(outCon);
                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                        }
                                                                    }
                                                                    __state_vectorize_inner_graph_5_streamOut_state:
                                                                    {
                                                                        _A_out_unroll.push(dace::Read<float, 16>(A_out_buf));
                                                                        #pragma HLS DEPENDENCE variable=A_out_buf false
                                                                    }
                                                                    __state_exit_vectorize_inner_graph_5_sdfg:;
                                                                }    ///////////////////

                                                            }
                                                        }
                                                    }
                                                }
                                                __state_exit_tile_sdfg_5_sdfg:;
                                            }    ///////////////////

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            __state_exit_ger_fpga_stream_rowTiles_5_sdfg:;
        }    ///////////////////

    }
}

void module_GER6(dace::FIFO<float, 16, 32> &_RES_to_GEMV6_A_0, dace::FIFO<float, 16, 32> &f_A_ger_GER6_0, dace::FIFO<float, 16, 32> &f_x_ger_GER6_0, dace::FIFO<float, 1, 32> &f_y6_ger__y_rS, float a, int n) {
    {
        auto ___A = dace::make_streamview(f_A_ger_GER6_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_ger_GER6_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(f_y6_ger__y_rS);
        auto &_y = ___y;
        auto ___RES = dace::make_streamview(_RES_to_GEMV6_A_0);
        auto &_RES = ___RES;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_ger_fpga_stream_rowTiles_6_ger_compute:
            {
                dace::vec<float, 1> y_buf_row[8192];
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            for (int j = 0; j < (n / 8192); j += 1) {
                                {
                                    for (int ii = 0; ii < 8192; ii += 1) {
                                        {
                                            auto ___A_tile = _A;
                                            auto &_A_tile = ___A_tile;
                                            auto ___x_tile = _x;
                                            auto &_x_tile = ___x_tile;
                                            auto ___y_tile = _y;
                                            auto &_y_tile = ___y_tile;
                                            auto ___A_out_tile = _RES;
                                            auto &_A_out_tile = ___A_out_tile;
                                            auto ___y_buf_tile = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_buf_row, 1);
                                            auto *_y_buf_tile = ___y_buf_tile.ptr<1>();

                                            {    ///////////////////
                                                int __dacesym_a = a;
                                                int __dacesym_ii = ii;
                                                int __dacesym_j = j;
                                                int __dacesym_n = n;
                                                auto a = __dacesym_a;
                                                auto ii = __dacesym_ii;
                                                auto j = __dacesym_j;
                                                auto n = __dacesym_n;

                                                __state_tile_sdfg_6_init_state_tile:
                                                ;
                                                if ((j == 0)) {
                                                    __state_tile_sdfg_6_read_y_reduceTile:
                                                    {
                                                        dace::vec<float, 1> y_buf[1];
                                                        #pragma HLS ARRAY_PARTITION variable=y_buf complete
                                                        dace::Write<float, 1>(y_buf, dace::Read<float, 1>(_y_tile.pop()));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        dace::Write<float, 1>(_y_buf_tile + ii, dace::Read<float, 1>(y_buf));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        #pragma HLS DEPENDENCE variable=_y_buf_tile false
                                                    }
                                                    __state_exit_tile_sdfg_6_init_state_tile_then:;
                                                    } else {
                                                    __state_tile_sdfg_6_read_empty_reduceTile:
                                                    ;
                                                    __state_exit_tile_sdfg_6_init_state_tile_else:;
                                                }
                                                __state_tile_sdfg_6_copmute_state_tile:
                                                {
                                                    dace::vec<float, 16> x_buf[(8192 / 16)];
                                                    {
                                                        for (int jj = 0; jj < 512; jj += 1) {
                                                            #pragma HLS PIPELINE II=1
                                                            #pragma HLS LOOP_FLATTEN
                                                            {
                                                                auto ___A_unroll = _A_tile;
                                                                auto &_A_unroll = ___A_unroll;
                                                                auto ___x_unroll = _x_tile;
                                                                auto &_x_unroll = ___x_unroll;
                                                                auto ___y_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (_y_buf_tile, 1);
                                                                auto *_y_unroll = ___y_unroll.ptr<1>();
                                                                auto ___A_out_unroll = _A_out_tile;
                                                                auto &_A_out_unroll = ___A_out_unroll;
                                                                auto ___x_buf_unroll = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                auto *_x_buf_unroll = ___x_buf_unroll.ptr<16>();

                                                                {    ///////////////////
                                                                    int __dacesym_a = a;
                                                                    int __dacesym_ii = ii;
                                                                    int __dacesym_jj = jj;
                                                                    auto a = __dacesym_a;
                                                                    auto ii = __dacesym_ii;
                                                                    auto jj = __dacesym_jj;
                                                                    dace::vec<float, 16> A_out_buf;

                                                                    __state_vectorize_inner_graph_6_init_state:
                                                                    ;
                                                                    if ((ii == 0)) {
                                                                        __state_vectorize_inner_graph_6_readX_state:
                                                                        {
                                                                            {
                                                                                auto __inCon = _x_unroll;
                                                                                auto inCon = __inCon.pop();

                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                                dace::vec<float, 16> outCon;

                                                                                ////////////////////
                                                                                // Tasklet code (streamToLocal_map)
                                                                                outCon = inCon;
                                                                                ////////////////////

                                                                                __outCon.write(outCon);
                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                            }
                                                                        }
                                                                        __state_exit_vectorize_inner_graph_6_init_state_then:;
                                                                        } else {
                                                                        __state_vectorize_inner_graph_6_readEmpty_state:
                                                                        ;
                                                                        __state_exit_vectorize_inner_graph_6_init_state_else:;
                                                                    }
                                                                    __state_vectorize_inner_graph_6_compute_state:
                                                                    {
                                                                        {
                                                                            auto __A_con = _A_unroll;
                                                                            auto A_con = __A_con.pop();
                                                                            auto __x_con = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                            dace::vec<float, 16> x_con = __x_con.val<16>();
                                                                            auto __y_con = dace::ArrayViewIn<float, 0, 1, 1> (_y_unroll + ii);
                                                                            dace::vec<float, 1> y_con = __y_con.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&A_out_buf);
                                                                            dace::vec<float, 16> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (compute_task)
                                                                            outCon = (A_con + ((x_con * y_con) * a));
                                                                            ////////////////////

                                                                            __outCon.write(outCon);
                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                        }
                                                                    }
                                                                    __state_vectorize_inner_graph_6_streamOut_state:
                                                                    {
                                                                        _A_out_unroll.push(dace::Read<float, 16>(A_out_buf));
                                                                        #pragma HLS DEPENDENCE variable=A_out_buf false
                                                                    }
                                                                    __state_exit_vectorize_inner_graph_6_sdfg:;
                                                                }    ///////////////////

                                                            }
                                                        }
                                                    }
                                                }
                                                __state_exit_tile_sdfg_6_sdfg:;
                                            }    ///////////////////

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            __state_exit_ger_fpga_stream_rowTiles_6_sdfg:;
        }    ///////////////////

    }
}

void module_GER7(dace::FIFO<float, 16, 32> &_RES_to_GEMV7_A_0, dace::FIFO<float, 16, 32> &f_A_ger_GER7_0, dace::FIFO<float, 16, 32> &f_x_ger_GER7_0, dace::FIFO<float, 1, 32> &f_y7_ger__y_rS, float a, int n) {
    {
        auto ___A = dace::make_streamview(f_A_ger_GER7_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_ger_GER7_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(f_y7_ger__y_rS);
        auto &_y = ___y;
        auto ___RES = dace::make_streamview(_RES_to_GEMV7_A_0);
        auto &_RES = ___RES;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_ger_fpga_stream_rowTiles_7_ger_compute:
            {
                dace::vec<float, 1> y_buf_row[8192];
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            for (int j = 0; j < (n / 8192); j += 1) {
                                {
                                    for (int ii = 0; ii < 8192; ii += 1) {
                                        {
                                            auto ___A_tile = _A;
                                            auto &_A_tile = ___A_tile;
                                            auto ___x_tile = _x;
                                            auto &_x_tile = ___x_tile;
                                            auto ___y_tile = _y;
                                            auto &_y_tile = ___y_tile;
                                            auto ___A_out_tile = _RES;
                                            auto &_A_out_tile = ___A_out_tile;
                                            auto ___y_buf_tile = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_buf_row, 1);
                                            auto *_y_buf_tile = ___y_buf_tile.ptr<1>();

                                            {    ///////////////////
                                                int __dacesym_a = a;
                                                int __dacesym_ii = ii;
                                                int __dacesym_j = j;
                                                int __dacesym_n = n;
                                                auto a = __dacesym_a;
                                                auto ii = __dacesym_ii;
                                                auto j = __dacesym_j;
                                                auto n = __dacesym_n;

                                                __state_tile_sdfg_7_init_state_tile:
                                                ;
                                                if ((j == 0)) {
                                                    __state_tile_sdfg_7_read_y_reduceTile:
                                                    {
                                                        dace::vec<float, 1> y_buf[1];
                                                        #pragma HLS ARRAY_PARTITION variable=y_buf complete
                                                        dace::Write<float, 1>(y_buf, dace::Read<float, 1>(_y_tile.pop()));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        dace::Write<float, 1>(_y_buf_tile + ii, dace::Read<float, 1>(y_buf));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        #pragma HLS DEPENDENCE variable=_y_buf_tile false
                                                    }
                                                    __state_exit_tile_sdfg_7_init_state_tile_then:;
                                                    } else {
                                                    __state_tile_sdfg_7_read_empty_reduceTile:
                                                    ;
                                                    __state_exit_tile_sdfg_7_init_state_tile_else:;
                                                }
                                                __state_tile_sdfg_7_copmute_state_tile:
                                                {
                                                    dace::vec<float, 16> x_buf[(8192 / 16)];
                                                    {
                                                        for (int jj = 0; jj < 512; jj += 1) {
                                                            #pragma HLS PIPELINE II=1
                                                            #pragma HLS LOOP_FLATTEN
                                                            {
                                                                auto ___A_unroll = _A_tile;
                                                                auto &_A_unroll = ___A_unroll;
                                                                auto ___x_unroll = _x_tile;
                                                                auto &_x_unroll = ___x_unroll;
                                                                auto ___y_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (_y_buf_tile, 1);
                                                                auto *_y_unroll = ___y_unroll.ptr<1>();
                                                                auto ___A_out_unroll = _A_out_tile;
                                                                auto &_A_out_unroll = ___A_out_unroll;
                                                                auto ___x_buf_unroll = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                auto *_x_buf_unroll = ___x_buf_unroll.ptr<16>();

                                                                {    ///////////////////
                                                                    int __dacesym_a = a;
                                                                    int __dacesym_ii = ii;
                                                                    int __dacesym_jj = jj;
                                                                    auto a = __dacesym_a;
                                                                    auto ii = __dacesym_ii;
                                                                    auto jj = __dacesym_jj;
                                                                    dace::vec<float, 16> A_out_buf;

                                                                    __state_vectorize_inner_graph_7_init_state:
                                                                    ;
                                                                    if ((ii == 0)) {
                                                                        __state_vectorize_inner_graph_7_readX_state:
                                                                        {
                                                                            {
                                                                                auto __inCon = _x_unroll;
                                                                                auto inCon = __inCon.pop();

                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                                dace::vec<float, 16> outCon;

                                                                                ////////////////////
                                                                                // Tasklet code (streamToLocal_map)
                                                                                outCon = inCon;
                                                                                ////////////////////

                                                                                __outCon.write(outCon);
                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                            }
                                                                        }
                                                                        __state_exit_vectorize_inner_graph_7_init_state_then:;
                                                                        } else {
                                                                        __state_vectorize_inner_graph_7_readEmpty_state:
                                                                        ;
                                                                        __state_exit_vectorize_inner_graph_7_init_state_else:;
                                                                    }
                                                                    __state_vectorize_inner_graph_7_compute_state:
                                                                    {
                                                                        {
                                                                            auto __A_con = _A_unroll;
                                                                            auto A_con = __A_con.pop();
                                                                            auto __x_con = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                            dace::vec<float, 16> x_con = __x_con.val<16>();
                                                                            auto __y_con = dace::ArrayViewIn<float, 0, 1, 1> (_y_unroll + ii);
                                                                            dace::vec<float, 1> y_con = __y_con.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&A_out_buf);
                                                                            dace::vec<float, 16> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (compute_task)
                                                                            outCon = (A_con + ((x_con * y_con) * a));
                                                                            ////////////////////

                                                                            __outCon.write(outCon);
                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                        }
                                                                    }
                                                                    __state_vectorize_inner_graph_7_streamOut_state:
                                                                    {
                                                                        _A_out_unroll.push(dace::Read<float, 16>(A_out_buf));
                                                                        #pragma HLS DEPENDENCE variable=A_out_buf false
                                                                    }
                                                                    __state_exit_vectorize_inner_graph_7_sdfg:;
                                                                }    ///////////////////

                                                            }
                                                        }
                                                    }
                                                }
                                                __state_exit_tile_sdfg_7_sdfg:;
                                            }    ///////////////////

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            __state_exit_ger_fpga_stream_rowTiles_7_sdfg:;
        }    ///////////////////

    }
}

void module_GER8(dace::FIFO<float, 16, 32> &_RES_to_GEMV8_A_0, dace::FIFO<float, 16, 32> &f_A_ger_GER8_0, dace::FIFO<float, 16, 32> &f_x_ger_GER8_0, dace::FIFO<float, 1, 32> &f_y8_ger__y_rS, float a, int n) {
    {
        auto ___A = dace::make_streamview(f_A_ger_GER8_0);
        auto &_A = ___A;
        auto ___x = dace::make_streamview(f_x_ger_GER8_0);
        auto &_x = ___x;
        auto ___y = dace::make_streamview(f_y8_ger__y_rS);
        auto &_y = ___y;
        auto ___RES = dace::make_streamview(_RES_to_GEMV8_A_0);
        auto &_RES = ___RES;

        {    ///////////////////
            int __dacesym_a = a;
            int __dacesym_n = n;
            auto a = __dacesym_a;
            auto n = __dacesym_n;

            __state_ger_fpga_stream_rowTiles_ger_compute:
            {
                dace::vec<float, 1> y_buf_row[8192];
                {
                    for (int i = 0; i < (n / 8192); i += 1) {
                        {
                            for (int j = 0; j < (n / 8192); j += 1) {
                                {
                                    for (int ii = 0; ii < 8192; ii += 1) {
                                        {
                                            auto ___A_tile = _A;
                                            auto &_A_tile = ___A_tile;
                                            auto ___x_tile = _x;
                                            auto &_x_tile = ___x_tile;
                                            auto ___y_tile = _y;
                                            auto &_y_tile = ___y_tile;
                                            auto ___A_out_tile = _RES;
                                            auto &_A_out_tile = ___A_out_tile;
                                            auto ___y_buf_tile = dace::ArrayViewOut<float, 1, 1, dace::NA_RUNTIME> (y_buf_row, 1);
                                            auto *_y_buf_tile = ___y_buf_tile.ptr<1>();

                                            {    ///////////////////
                                                int __dacesym_a = a;
                                                int __dacesym_ii = ii;
                                                int __dacesym_j = j;
                                                int __dacesym_n = n;
                                                auto a = __dacesym_a;
                                                auto ii = __dacesym_ii;
                                                auto j = __dacesym_j;
                                                auto n = __dacesym_n;

                                                __state_tile_sdfg_init_state_tile:
                                                ;
                                                if ((j == 0)) {
                                                    __state_tile_sdfg_read_y_reduceTile:
                                                    {
                                                        dace::vec<float, 1> y_buf[1];
                                                        #pragma HLS ARRAY_PARTITION variable=y_buf complete
                                                        dace::Write<float, 1>(y_buf, dace::Read<float, 1>(_y_tile.pop()));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        dace::Write<float, 1>(_y_buf_tile + ii, dace::Read<float, 1>(y_buf));
                                                        #pragma HLS DEPENDENCE variable=y_buf false
                                                        #pragma HLS DEPENDENCE variable=_y_buf_tile false
                                                    }
                                                    __state_exit_tile_sdfg_init_state_tile_then:;
                                                    } else {
                                                    __state_tile_sdfg_read_empty_reduceTile:
                                                    ;
                                                    __state_exit_tile_sdfg_init_state_tile_else:;
                                                }
                                                __state_tile_sdfg_copmute_state_tile:
                                                {
                                                    dace::vec<float, 16> x_buf[(8192 / 16)];
                                                    {
                                                        for (int jj = 0; jj < 512; jj += 1) {
                                                            #pragma HLS PIPELINE II=1
                                                            #pragma HLS LOOP_FLATTEN
                                                            {
                                                                auto ___A_unroll = _A_tile;
                                                                auto &_A_unroll = ___A_unroll;
                                                                auto ___x_unroll = _x_tile;
                                                                auto &_x_unroll = ___x_unroll;
                                                                auto ___y_unroll = dace::ArrayViewIn<float, 1, 1, dace::NA_RUNTIME> (_y_buf_tile, 1);
                                                                auto *_y_unroll = ___y_unroll.ptr<1>();
                                                                auto ___A_out_unroll = _A_out_tile;
                                                                auto &_A_out_unroll = ___A_out_unroll;
                                                                auto ___x_buf_unroll = dace::ArrayViewOut<float, 1, 16, dace::NA_RUNTIME> (x_buf, 1);
                                                                auto *_x_buf_unroll = ___x_buf_unroll.ptr<16>();

                                                                {    ///////////////////
                                                                    int __dacesym_a = a;
                                                                    int __dacesym_ii = ii;
                                                                    int __dacesym_jj = jj;
                                                                    auto a = __dacesym_a;
                                                                    auto ii = __dacesym_ii;
                                                                    auto jj = __dacesym_jj;
                                                                    dace::vec<float, 16> A_out_buf;

                                                                    __state_vectorize_inner_graph_init_state:
                                                                    ;
                                                                    if ((ii == 0)) {
                                                                        __state_vectorize_inner_graph_readX_state:
                                                                        {
                                                                            {
                                                                                auto __inCon = _x_unroll;
                                                                                auto inCon = __inCon.pop();

                                                                                auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                                dace::vec<float, 16> outCon;

                                                                                ////////////////////
                                                                                // Tasklet code (streamToLocal_map)
                                                                                outCon = inCon;
                                                                                ////////////////////

                                                                                __outCon.write(outCon);
                                                                                #pragma HLS DEPENDENCE variable=outCon false
                                                                            }
                                                                        }
                                                                        __state_exit_vectorize_inner_graph_init_state_then:;
                                                                        } else {
                                                                        __state_vectorize_inner_graph_readEmpty_state:
                                                                        ;
                                                                        __state_exit_vectorize_inner_graph_init_state_else:;
                                                                    }
                                                                    __state_vectorize_inner_graph_compute_state:
                                                                    {
                                                                        {
                                                                            auto __A_con = _A_unroll;
                                                                            auto A_con = __A_con.pop();
                                                                            auto __x_con = dace::ArrayViewIn<float, 0, 16, 1> (_x_buf_unroll + jj);
                                                                            dace::vec<float, 16> x_con = __x_con.val<16>();
                                                                            auto __y_con = dace::ArrayViewIn<float, 0, 1, 1> (_y_unroll + ii);
                                                                            dace::vec<float, 1> y_con = __y_con.val<1>();

                                                                            auto __outCon = dace::ArrayViewOut<float, 0, 16, 1> (&A_out_buf);
                                                                            dace::vec<float, 16> outCon;

                                                                            ////////////////////
                                                                            // Tasklet code (compute_task)
                                                                            outCon = (A_con + ((x_con * y_con) * a));
                                                                            ////////////////////

                                                                            __outCon.write(outCon);
                                                                            #pragma HLS DEPENDENCE variable=outCon false
                                                                        }
                                                                    }
                                                                    __state_vectorize_inner_graph_streamOut_state:
                                                                    {
                                                                        _A_out_unroll.push(dace::Read<float, 16>(A_out_buf));
                                                                        #pragma HLS DEPENDENCE variable=A_out_buf false
                                                                    }
                                                                    __state_exit_vectorize_inner_graph_sdfg:;
                                                                }    ///////////////////

                                                            }
                                                        }
                                                    }
                                                }
                                                __state_exit_tile_sdfg_sdfg:;
                                            }    ///////////////////

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            __state_exit_ger_fpga_stream_rowTiles_sdfg:;
        }    ///////////////////

    }
}

void module_forkTask_f_A_ger__fk_rS(dace::FIFO<float, 16, 32> &f_A_ger_GER1_0, dace::FIFO<float, 16, 32> &f_A_ger_GER2_0, dace::FIFO<float, 16, 32> &f_A_ger_GER3_0, dace::FIFO<float, 16, 32> &f_A_ger_GER4_0, dace::FIFO<float, 16, 32> &f_A_ger_GER5_0, dace::FIFO<float, 16, 32> &f_A_ger_GER6_0, dace::FIFO<float, 16, 32> &f_A_ger_GER7_0, dace::FIFO<float, 16, 32> &f_A_ger_GER8_0, dace::FIFO<float, 16, 32> &f_A_ger__fk_rS, float a, int n) {
    {
        for (int i = 0; i < ((n * n) / 16); i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::make_streamview(f_A_ger__fk_rS);
                auto inCon = __inCon.pop();

                auto __outCon0 = dace::make_streamview(f_A_ger_GER1_0);
                dace::vec<float, 16> outCon0;
                auto __outCon1 = dace::make_streamview(f_A_ger_GER2_0);
                dace::vec<float, 16> outCon1;
                auto __outCon2 = dace::make_streamview(f_A_ger_GER3_0);
                dace::vec<float, 16> outCon2;
                auto __outCon3 = dace::make_streamview(f_A_ger_GER4_0);
                dace::vec<float, 16> outCon3;
                auto __outCon4 = dace::make_streamview(f_A_ger_GER5_0);
                dace::vec<float, 16> outCon4;
                auto __outCon5 = dace::make_streamview(f_A_ger_GER6_0);
                dace::vec<float, 16> outCon5;
                auto __outCon6 = dace::make_streamview(f_A_ger_GER7_0);
                dace::vec<float, 16> outCon6;
                auto __outCon7 = dace::make_streamview(f_A_ger_GER8_0);
                dace::vec<float, 16> outCon7;

                ////////////////////
                // Tasklet code (forkTask_f_A_ger__fk_rS)
                outCon0 = inCon;
                outCon1 = inCon;
                outCon2 = inCon;
                outCon3 = inCon;
                outCon4 = inCon;
                outCon5 = inCon;
                outCon6 = inCon;
                outCon7 = inCon;
                ////////////////////

                __outCon0.write(outCon0);
                __outCon1.write(outCon1);
                __outCon2.write(outCon2);
                __outCon3.write(outCon3);
                __outCon4.write(outCon4);
                __outCon5.write(outCon5);
                __outCon6.write(outCon6);
                __outCon7.write(outCon7);
            }
        }
    }
}

void module_sR_f_x_ger__fk_rS(dace::vec<float, 16> const *f_x_ger_in, dace::FIFO<float, 16, 32> &f_x_ger__fk_rS, float a, int n) {

    dace::ArrayInterface<float, 16> f_x_ger(f_x_ger_in, nullptr);

    {
        for (int r = 0; r < (n / 8192); r += 1) {
            {
                for (int i = 0; i < (n / 16); i += 1) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS LOOP_FLATTEN
                    {
                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (f_x_ger + i);
                        dace::vec<float, 16> inCon = __inCon.val<16>();

                        auto __outCon = dace::make_streamview(f_x_ger__fk_rS);
                        dace::vec<float, 16> outCon;

                        ////////////////////
                        // Tasklet code (sR_f_x_ger__fk_rS)
                        outCon = inCon;
                        ////////////////////

                        __outCon.write(outCon);
                    }
                }
            }
        }
    }
}

void module_forkTask_f_x_ger__fk_rS(dace::FIFO<float, 16, 32> &f_x_ger_GER1_0, dace::FIFO<float, 16, 32> &f_x_ger_GER2_0, dace::FIFO<float, 16, 32> &f_x_ger_GER3_0, dace::FIFO<float, 16, 32> &f_x_ger_GER4_0, dace::FIFO<float, 16, 32> &f_x_ger_GER5_0, dace::FIFO<float, 16, 32> &f_x_ger_GER6_0, dace::FIFO<float, 16, 32> &f_x_ger_GER7_0, dace::FIFO<float, 16, 32> &f_x_ger_GER8_0, dace::FIFO<float, 16, 32> &f_x_ger__fk_rS, float a, int n) {
    {
        for (int i = 0; i < ((n * n) / 131072); i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::make_streamview(f_x_ger__fk_rS);
                auto inCon = __inCon.pop();

                auto __outCon0 = dace::make_streamview(f_x_ger_GER1_0);
                dace::vec<float, 16> outCon0;
                auto __outCon1 = dace::make_streamview(f_x_ger_GER2_0);
                dace::vec<float, 16> outCon1;
                auto __outCon2 = dace::make_streamview(f_x_ger_GER3_0);
                dace::vec<float, 16> outCon2;
                auto __outCon3 = dace::make_streamview(f_x_ger_GER4_0);
                dace::vec<float, 16> outCon3;
                auto __outCon4 = dace::make_streamview(f_x_ger_GER5_0);
                dace::vec<float, 16> outCon4;
                auto __outCon5 = dace::make_streamview(f_x_ger_GER6_0);
                dace::vec<float, 16> outCon5;
                auto __outCon6 = dace::make_streamview(f_x_ger_GER7_0);
                dace::vec<float, 16> outCon6;
                auto __outCon7 = dace::make_streamview(f_x_ger_GER8_0);
                dace::vec<float, 16> outCon7;

                ////////////////////
                // Tasklet code (forkTask_f_x_ger__fk_rS)
                outCon0 = inCon;
                outCon1 = inCon;
                outCon2 = inCon;
                outCon3 = inCon;
                outCon4 = inCon;
                outCon5 = inCon;
                outCon6 = inCon;
                outCon7 = inCon;
                ////////////////////

                __outCon0.write(outCon0);
                __outCon1.write(outCon1);
                __outCon2.write(outCon2);
                __outCon3.write(outCon3);
                __outCon4.write(outCon4);
                __outCon5.write(outCon5);
                __outCon6.write(outCon6);
                __outCon7.write(outCon7);
            }
        }
    }
}

void module_sR_f_y1_ger__y_rS(dace::vec<float, 1> const *f_y1_ger_in, dace::FIFO<float, 1, 32> &f_y1_ger__y_rS, float a, int n) {

    dace::ArrayInterface<float, 1> f_y1_ger(f_y1_ger_in, nullptr);

    {
        for (int i = 0; i < n; i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (f_y1_ger + i);
                dace::vec<float, 1> inCon = __inCon.val<1>();

                auto __outCon = dace::make_streamview(f_y1_ger__y_rS);
                dace::vec<float, 1> outCon;

                ////////////////////
                // Tasklet code (sR_f_y1_ger__y_rS)
                outCon = inCon;
                ////////////////////

                __outCon.write(outCon);
            }
        }
    }
}

void module_sR_f_y2_ger__y_rS(dace::vec<float, 1> const *f_y2_ger_in, dace::FIFO<float, 1, 32> &f_y2_ger__y_rS, float a, int n) {

    dace::ArrayInterface<float, 1> f_y2_ger(f_y2_ger_in, nullptr);

    {
        for (int i = 0; i < n; i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (f_y2_ger + i);
                dace::vec<float, 1> inCon = __inCon.val<1>();

                auto __outCon = dace::make_streamview(f_y2_ger__y_rS);
                dace::vec<float, 1> outCon;

                ////////////////////
                // Tasklet code (sR_f_y2_ger__y_rS)
                outCon = inCon;
                ////////////////////

                __outCon.write(outCon);
            }
        }
    }
}

void module_sR_f_y3_ger__y_rS(dace::vec<float, 1> const *f_y3_ger_in, dace::FIFO<float, 1, 32> &f_y3_ger__y_rS, float a, int n) {

    dace::ArrayInterface<float, 1> f_y3_ger(f_y3_ger_in, nullptr);

    {
        for (int i = 0; i < n; i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (f_y3_ger + i);
                dace::vec<float, 1> inCon = __inCon.val<1>();

                auto __outCon = dace::make_streamview(f_y3_ger__y_rS);
                dace::vec<float, 1> outCon;

                ////////////////////
                // Tasklet code (sR_f_y3_ger__y_rS)
                outCon = inCon;
                ////////////////////

                __outCon.write(outCon);
            }
        }
    }
}

void module_sR_f_y4_ger__y_rS(dace::vec<float, 1> const *f_y4_ger_in, dace::FIFO<float, 1, 32> &f_y4_ger__y_rS, float a, int n) {

    dace::ArrayInterface<float, 1> f_y4_ger(f_y4_ger_in, nullptr);

    {
        for (int i = 0; i < n; i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (f_y4_ger + i);
                dace::vec<float, 1> inCon = __inCon.val<1>();

                auto __outCon = dace::make_streamview(f_y4_ger__y_rS);
                dace::vec<float, 1> outCon;

                ////////////////////
                // Tasklet code (sR_f_y4_ger__y_rS)
                outCon = inCon;
                ////////////////////

                __outCon.write(outCon);
            }
        }
    }
}

void module_sR_f_y5_ger__y_rS(dace::vec<float, 1> const *f_y5_ger_in, dace::FIFO<float, 1, 32> &f_y5_ger__y_rS, float a, int n) {

    dace::ArrayInterface<float, 1> f_y5_ger(f_y5_ger_in, nullptr);

    {
        for (int i = 0; i < n; i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (f_y5_ger + i);
                dace::vec<float, 1> inCon = __inCon.val<1>();

                auto __outCon = dace::make_streamview(f_y5_ger__y_rS);
                dace::vec<float, 1> outCon;

                ////////////////////
                // Tasklet code (sR_f_y5_ger__y_rS)
                outCon = inCon;
                ////////////////////

                __outCon.write(outCon);
            }
        }
    }
}

void module_sR_f_y6_ger__y_rS(dace::vec<float, 1> const *f_y6_ger_in, dace::FIFO<float, 1, 32> &f_y6_ger__y_rS, float a, int n) {

    dace::ArrayInterface<float, 1> f_y6_ger(f_y6_ger_in, nullptr);

    {
        for (int i = 0; i < n; i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (f_y6_ger + i);
                dace::vec<float, 1> inCon = __inCon.val<1>();

                auto __outCon = dace::make_streamview(f_y6_ger__y_rS);
                dace::vec<float, 1> outCon;

                ////////////////////
                // Tasklet code (sR_f_y6_ger__y_rS)
                outCon = inCon;
                ////////////////////

                __outCon.write(outCon);
            }
        }
    }
}

void module_sR_f_y7_ger__y_rS(dace::vec<float, 1> const *f_y7_ger_in, dace::FIFO<float, 1, 32> &f_y7_ger__y_rS, float a, int n) {

    dace::ArrayInterface<float, 1> f_y7_ger(f_y7_ger_in, nullptr);

    {
        for (int i = 0; i < n; i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (f_y7_ger + i);
                dace::vec<float, 1> inCon = __inCon.val<1>();

                auto __outCon = dace::make_streamview(f_y7_ger__y_rS);
                dace::vec<float, 1> outCon;

                ////////////////////
                // Tasklet code (sR_f_y7_ger__y_rS)
                outCon = inCon;
                ////////////////////

                __outCon.write(outCon);
            }
        }
    }
}

void module_sR_f_y8_ger__y_rS(dace::vec<float, 1> const *f_y8_ger_in, dace::FIFO<float, 1, 32> &f_y8_ger__y_rS, float a, int n) {

    dace::ArrayInterface<float, 1> f_y8_ger(f_y8_ger_in, nullptr);

    {
        for (int i = 0; i < n; i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::ArrayViewIn<float, 0, 1, 1> (f_y8_ger + i);
                dace::vec<float, 1> inCon = __inCon.val<1>();

                auto __outCon = dace::make_streamview(f_y8_ger__y_rS);
                dace::vec<float, 1> outCon;

                ////////////////////
                // Tasklet code (sR_f_y8_ger__y_rS)
                outCon = inCon;
                ////////////////////

                __outCon.write(outCon);
            }
        }
    }
}

void module_sR_f_x_gemv__fk_rS(dace::vec<float, 16> const *f_x_gemv_in, dace::FIFO<float, 16, 32> &f_x_gemv__fk_rS, float a, int n) {

    dace::ArrayInterface<float, 16> f_x_gemv(f_x_gemv_in, nullptr);

    {
        for (int r = 0; r < (n / 8192); r += 1) {
            {
                for (int i = 0; i < (n / 16); i += 1) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS LOOP_FLATTEN
                    {
                        auto __inCon = dace::ArrayViewIn<float, 0, 16, 1> (f_x_gemv + i);
                        dace::vec<float, 16> inCon = __inCon.val<16>();

                        auto __outCon = dace::make_streamview(f_x_gemv__fk_rS);
                        dace::vec<float, 16> outCon;

                        ////////////////////
                        // Tasklet code (sR_f_x_gemv__fk_rS)
                        outCon = inCon;
                        ////////////////////

                        __outCon.write(outCon);
                    }
                }
            }
        }
    }
}

void module_forkTask_f_x_gemv__fk_rS(dace::FIFO<float, 16, 32> &f_x_gemv_GEMV1_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV2_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV3_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV4_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV5_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV6_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV7_0, dace::FIFO<float, 16, 32> &f_x_gemv_GEMV8_0, dace::FIFO<float, 16, 32> &f_x_gemv__fk_rS, float a, int n) {
    {
        for (int i = 0; i < ((n * n) / 131072); i += 1) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_FLATTEN
            {
                auto __inCon = dace::make_streamview(f_x_gemv__fk_rS);
                auto inCon = __inCon.pop();

                auto __outCon0 = dace::make_streamview(f_x_gemv_GEMV1_0);
                dace::vec<float, 16> outCon0;
                auto __outCon1 = dace::make_streamview(f_x_gemv_GEMV2_0);
                dace::vec<float, 16> outCon1;
                auto __outCon2 = dace::make_streamview(f_x_gemv_GEMV3_0);
                dace::vec<float, 16> outCon2;
                auto __outCon3 = dace::make_streamview(f_x_gemv_GEMV4_0);
                dace::vec<float, 16> outCon3;
                auto __outCon4 = dace::make_streamview(f_x_gemv_GEMV5_0);
                dace::vec<float, 16> outCon4;
                auto __outCon5 = dace::make_streamview(f_x_gemv_GEMV6_0);
                dace::vec<float, 16> outCon5;
                auto __outCon6 = dace::make_streamview(f_x_gemv_GEMV7_0);
                dace::vec<float, 16> outCon6;
                auto __outCon7 = dace::make_streamview(f_x_gemv_GEMV8_0);
                dace::vec<float, 16> outCon7;

                ////////////////////
                // Tasklet code (forkTask_f_x_gemv__fk_rS)
                outCon0 = inCon;
                outCon1 = inCon;
                outCon2 = inCon;
                outCon3 = inCon;
                outCon4 = inCon;
                outCon5 = inCon;
                outCon6 = inCon;
                outCon7 = inCon;
                ////////////////////

                __outCon0.write(outCon0);
                __outCon1.write(outCon1);
                __outCon2.write(outCon2);
                __outCon3.write(outCon3);
                __outCon4.write(outCon4);
                __outCon5.write(outCon5);
                __outCon6.write(outCon6);
                __outCon7.write(outCon7);
            }
        }
    }
}

void module_sW_fpga_res(dace::vec<float, 1> *fpga_res_out, dace::FIFO<float, 1, 32> &fpga_res__res_wS, float a, int n) {

    dace::ArrayInterface<float, 1> fpga_res(nullptr, fpga_res_out);

    {
        {
            const int i = 0; // Degenerate loop
            {
                auto __inCon = dace::make_streamview(fpga_res__res_wS);
                auto inCon = __inCon.pop();

                auto __outCon = dace::ArrayViewOut<float, 0, 1, 1> (fpga_res + i);
                dace::vec<float, 1> outCon;

                ////////////////////
                // Tasklet code (sW_fpga_res)
                outCon = inCon;
                ////////////////////

                __outCon.write(outCon);
            }
        }
    }
}

DACE_EXPORTED void test_state(dace::vec<float, 16> *f_A_ger_in, dace::vec<float, 16> *f_x_gemv_in, dace::vec<float, 16> *f_x_ger_in, dace::vec<float, 1> *f_y1_ger_in, dace::vec<float, 1> *f_y2_ger_in, dace::vec<float, 1> *f_y3_ger_in, dace::vec<float, 1> *f_y4_ger_in, dace::vec<float, 1> *f_y5_ger_in, dace::vec<float, 1> *f_y6_ger_in, dace::vec<float, 1> *f_y7_ger_in, dace::vec<float, 1> *f_y8_ger_in, dace::vec<float, 1> *fpga_res_out, float a, int n) {
    #pragma HLS INTERFACE m_axi port=f_A_ger_in offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=f_x_gemv_in offset=slave bundle=gmem1
    #pragma HLS INTERFACE m_axi port=f_x_ger_in offset=slave bundle=gmem2
    #pragma HLS INTERFACE m_axi port=f_y1_ger_in offset=slave bundle=gmem3
    #pragma HLS INTERFACE m_axi port=f_y2_ger_in offset=slave bundle=gmem4
    #pragma HLS INTERFACE m_axi port=f_y3_ger_in offset=slave bundle=gmem5
    #pragma HLS INTERFACE m_axi port=f_y4_ger_in offset=slave bundle=gmem6
    #pragma HLS INTERFACE m_axi port=f_y5_ger_in offset=slave bundle=gmem7
    #pragma HLS INTERFACE m_axi port=f_y6_ger_in offset=slave bundle=gmem8
    #pragma HLS INTERFACE m_axi port=f_y7_ger_in offset=slave bundle=gmem9
    #pragma HLS INTERFACE m_axi port=f_y8_ger_in offset=slave bundle=gmem10
    #pragma HLS INTERFACE m_axi port=fpga_res_out offset=slave bundle=gmem11
    #pragma HLS INTERFACE s_axilite port=f_A_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_x_gemv_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_x_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_y1_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_y2_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_y3_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_y4_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_y5_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_y6_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_y7_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=f_y8_ger_in bundle=control
    #pragma HLS INTERFACE s_axilite port=fpga_res_out bundle=control
    #pragma HLS INTERFACE s_axilite port=a bundle=control
    #pragma HLS INTERFACE s_axilite port=n bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control
    
    #pragma HLS DATAFLOW
    
    HLSLIB_DATAFLOW_INIT();
    dace::FIFO<float, 1, 32> _res_to_saxpy_l1_1_y_0("_res_to_saxpy_l1_1_y_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l1_1_x_0("_res_to_saxpy_l1_1_x_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_x_0("_res_to_saxpy_x_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l2_2_y_0("_res_to_saxpy_l2_2_y_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l2_2_x_0("_res_to_saxpy_l2_2_x_0");
    dace::FIFO<float, 16, 32> _RES_to_GEMV8_A_0("_RES_to_GEMV8_A_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l2_4_y_0("_res_to_saxpy_l2_4_y_0");
    dace::FIFO<float, 16, 32> f_x_gemv_GEMV8_0("f_x_gemv_GEMV8_0");
    dace::FIFO<float, 16, 32> _RES_to_GEMV4_A_0("_RES_to_GEMV4_A_0");
    dace::FIFO<float, 16, 32> f_x_gemv_GEMV4_0("f_x_gemv_GEMV4_0");
    dace::FIFO<float, 16, 32> _RES_to_GEMV1_A_0("_RES_to_GEMV1_A_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l2_1_x_0("_res_to_saxpy_l2_1_x_0");
    dace::FIFO<float, 16, 32> f_x_gemv_GEMV1_0("f_x_gemv_GEMV1_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l1_2_x_0("_res_to_saxpy_l1_2_x_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l1_2_y_0("_res_to_saxpy_l1_2_y_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_y_0("_res_to_saxpy_y_0");
    dace::FIFO<float, 16, 32> _RES_to_GEMV2_A_0("_RES_to_GEMV2_A_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l2_1_y_0("_res_to_saxpy_l2_1_y_0");
    dace::FIFO<float, 16, 32> f_x_gemv_GEMV2_0("f_x_gemv_GEMV2_0");
    dace::FIFO<float, 16, 32> _RES_to_GEMV6_A_0("_RES_to_GEMV6_A_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l2_3_y_0("_res_to_saxpy_l2_3_y_0");
    dace::FIFO<float, 16, 32> f_x_gemv_GEMV6_0("f_x_gemv_GEMV6_0");
    dace::FIFO<float, 16, 32> _RES_to_GEMV3_A_0("_RES_to_GEMV3_A_0");
    dace::FIFO<float, 16, 32> f_x_gemv_GEMV3_0("f_x_gemv_GEMV3_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l2_3_x_0("_res_to_saxpy_l2_3_x_0");
    dace::FIFO<float, 16, 32> _RES_to_GEMV5_A_0("_RES_to_GEMV5_A_0");
    dace::FIFO<float, 16, 32> f_x_gemv_GEMV5_0("f_x_gemv_GEMV5_0");
    dace::FIFO<float, 1, 32> _res_to_blas_asum_x_0("_res_to_blas_asum_x_0");
    dace::FIFO<float, 16, 32> _RES_to_GEMV7_A_0("_RES_to_GEMV7_A_0");
    dace::FIFO<float, 1, 32> _res_to_saxpy_l2_4_x_0("_res_to_saxpy_l2_4_x_0");
    dace::FIFO<float, 16, 32> f_x_gemv_GEMV7_0("f_x_gemv_GEMV7_0");
    dace::FIFO<float, 1, 32> fpga_res__res_wS("fpga_res__res_wS");
    dace::FIFO<float, 16, 32> f_A_ger__fk_rS("f_A_ger__fk_rS");
    dace::FIFO<float, 16, 32> f_A_ger_GER1_0("f_A_ger_GER1_0");
    dace::FIFO<float, 16, 32> f_x_ger_GER1_0("f_x_ger_GER1_0");
    dace::FIFO<float, 1, 32> f_y1_ger__y_rS("f_y1_ger__y_rS");
    dace::FIFO<float, 16, 32> f_A_ger_GER2_0("f_A_ger_GER2_0");
    dace::FIFO<float, 16, 32> f_x_ger_GER2_0("f_x_ger_GER2_0");
    dace::FIFO<float, 1, 32> f_y2_ger__y_rS("f_y2_ger__y_rS");
    dace::FIFO<float, 16, 32> f_A_ger_GER3_0("f_A_ger_GER3_0");
    dace::FIFO<float, 16, 32> f_x_ger_GER3_0("f_x_ger_GER3_0");
    dace::FIFO<float, 1, 32> f_y3_ger__y_rS("f_y3_ger__y_rS");
    dace::FIFO<float, 16, 32> f_A_ger_GER4_0("f_A_ger_GER4_0");
    dace::FIFO<float, 16, 32> f_x_ger_GER4_0("f_x_ger_GER4_0");
    dace::FIFO<float, 1, 32> f_y4_ger__y_rS("f_y4_ger__y_rS");
    dace::FIFO<float, 16, 32> f_A_ger_GER5_0("f_A_ger_GER5_0");
    dace::FIFO<float, 16, 32> f_x_ger_GER5_0("f_x_ger_GER5_0");
    dace::FIFO<float, 1, 32> f_y5_ger__y_rS("f_y5_ger__y_rS");
    dace::FIFO<float, 16, 32> f_A_ger_GER6_0("f_A_ger_GER6_0");
    dace::FIFO<float, 16, 32> f_x_ger_GER6_0("f_x_ger_GER6_0");
    dace::FIFO<float, 1, 32> f_y6_ger__y_rS("f_y6_ger__y_rS");
    dace::FIFO<float, 16, 32> f_A_ger_GER7_0("f_A_ger_GER7_0");
    dace::FIFO<float, 16, 32> f_x_ger_GER7_0("f_x_ger_GER7_0");
    dace::FIFO<float, 1, 32> f_y7_ger__y_rS("f_y7_ger__y_rS");
    dace::FIFO<float, 16, 32> f_A_ger_GER8_0("f_A_ger_GER8_0");
    dace::FIFO<float, 16, 32> f_x_ger_GER8_0("f_x_ger_GER8_0");
    dace::FIFO<float, 1, 32> f_y8_ger__y_rS("f_y8_ger__y_rS");
    dace::FIFO<float, 16, 32> f_x_ger__fk_rS("f_x_ger__fk_rS");
    dace::FIFO<float, 16, 32> f_x_gemv__fk_rS("f_x_gemv__fk_rS");
    HLSLIB_DATAFLOW_FUNCTION(module_saxpy_l1_1, _res_to_saxpy_l1_1_x_0, _res_to_saxpy_l1_1_y_0, _res_to_saxpy_x_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_saxpy_l2_2, _res_to_saxpy_l1_1_y_0, _res_to_saxpy_l2_2_x_0, _res_to_saxpy_l2_2_y_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GEMV8, _RES_to_GEMV8_A_0, _res_to_saxpy_l2_4_y_0, f_x_gemv_GEMV8_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GEMV4, _RES_to_GEMV4_A_0, _res_to_saxpy_l2_2_y_0, f_x_gemv_GEMV4_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GEMV1, _RES_to_GEMV1_A_0, _res_to_saxpy_l2_1_x_0, f_x_gemv_GEMV1_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_saxpy_l1_2, _res_to_saxpy_l1_2_x_0, _res_to_saxpy_l1_2_y_0, _res_to_saxpy_y_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GEMV2, _RES_to_GEMV2_A_0, _res_to_saxpy_l2_1_y_0, f_x_gemv_GEMV2_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GEMV6, _RES_to_GEMV6_A_0, _res_to_saxpy_l2_3_y_0, f_x_gemv_GEMV6_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_saxpy_l2_1, _res_to_saxpy_l1_1_x_0, _res_to_saxpy_l2_1_x_0, _res_to_saxpy_l2_1_y_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GEMV3, _RES_to_GEMV3_A_0, _res_to_saxpy_l2_2_x_0, f_x_gemv_GEMV3_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_saxpy_l2_3, _res_to_saxpy_l1_2_x_0, _res_to_saxpy_l2_3_x_0, _res_to_saxpy_l2_3_y_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GEMV5, _RES_to_GEMV5_A_0, _res_to_saxpy_l2_3_x_0, f_x_gemv_GEMV5_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_saxpy, _res_to_blas_asum_x_0, _res_to_saxpy_x_0, _res_to_saxpy_y_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GEMV7, _RES_to_GEMV7_A_0, _res_to_saxpy_l2_4_x_0, f_x_gemv_GEMV7_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_saxpy_l2_4, _res_to_saxpy_l1_2_y_0, _res_to_saxpy_l2_4_x_0, _res_to_saxpy_l2_4_y_0, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_blas_asum, _res_to_blas_asum_x_0, fpga_res__res_wS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_A_ger__fk_rS, f_A_ger_in, f_A_ger__fk_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GER1, _RES_to_GEMV1_A_0, f_A_ger_GER1_0, f_x_ger_GER1_0, f_y1_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GER2, _RES_to_GEMV2_A_0, f_A_ger_GER2_0, f_x_ger_GER2_0, f_y2_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GER3, _RES_to_GEMV3_A_0, f_A_ger_GER3_0, f_x_ger_GER3_0, f_y3_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GER4, _RES_to_GEMV4_A_0, f_A_ger_GER4_0, f_x_ger_GER4_0, f_y4_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GER5, _RES_to_GEMV5_A_0, f_A_ger_GER5_0, f_x_ger_GER5_0, f_y5_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GER6, _RES_to_GEMV6_A_0, f_A_ger_GER6_0, f_x_ger_GER6_0, f_y6_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GER7, _RES_to_GEMV7_A_0, f_A_ger_GER7_0, f_x_ger_GER7_0, f_y7_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_GER8, _RES_to_GEMV8_A_0, f_A_ger_GER8_0, f_x_ger_GER8_0, f_y8_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_forkTask_f_A_ger__fk_rS, f_A_ger_GER1_0, f_A_ger_GER2_0, f_A_ger_GER3_0, f_A_ger_GER4_0, f_A_ger_GER5_0, f_A_ger_GER6_0, f_A_ger_GER7_0, f_A_ger_GER8_0, f_A_ger__fk_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_x_ger__fk_rS, f_x_ger_in, f_x_ger__fk_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_forkTask_f_x_ger__fk_rS, f_x_ger_GER1_0, f_x_ger_GER2_0, f_x_ger_GER3_0, f_x_ger_GER4_0, f_x_ger_GER5_0, f_x_ger_GER6_0, f_x_ger_GER7_0, f_x_ger_GER8_0, f_x_ger__fk_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_y1_ger__y_rS, f_y1_ger_in, f_y1_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_y2_ger__y_rS, f_y2_ger_in, f_y2_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_y3_ger__y_rS, f_y3_ger_in, f_y3_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_y4_ger__y_rS, f_y4_ger_in, f_y4_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_y5_ger__y_rS, f_y5_ger_in, f_y5_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_y6_ger__y_rS, f_y6_ger_in, f_y6_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_y7_ger__y_rS, f_y7_ger_in, f_y7_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_y8_ger__y_rS, f_y8_ger_in, f_y8_ger__y_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sR_f_x_gemv__fk_rS, f_x_gemv_in, f_x_gemv__fk_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_forkTask_f_x_gemv__fk_rS, f_x_gemv_GEMV1_0, f_x_gemv_GEMV2_0, f_x_gemv_GEMV3_0, f_x_gemv_GEMV4_0, f_x_gemv_GEMV5_0, f_x_gemv_GEMV6_0, f_x_gemv_GEMV7_0, f_x_gemv_GEMV8_0, f_x_gemv__fk_rS, a, n);
    HLSLIB_DATAFLOW_FUNCTION(module_sW_fpga_res, fpga_res_out, fpga_res__res_wS, a, n);
    HLSLIB_DATAFLOW_FINALIZE();
}
