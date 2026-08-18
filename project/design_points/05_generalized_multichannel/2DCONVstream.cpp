#include "2DCONV_stream.h"
#include <hls_stream.h>

#define MAX_WIDTH 128
#define K 3
#define PAD (K/2)

#define MAX_CIN  8
#define MAX_COUT 8

union float_bits { float f; unsigned u; };

static inline data_t unpack(ap_int<32> raw) {
    float_bits fb; fb.u = (unsigned)raw; return fb.f;
}
static inline ap_int<32> pack(data_t val) {
    float_bits fb; fb.f = val; return (ap_int<32>)fb.u;
}

void conv2d_stream(
    hls::stream<axis_pkt_t> &in_stream,
    hls::stream<axis_pkt_t> &out_stream,
    int rows, int cols,
    int Cin, int Cout,
    data_t kernel[MAX_COUT][MAX_CIN][K*K]
)
{
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream
#pragma HLS INTERFACE s_axilite port=rows  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=cols  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=Cin   bundle=CTRL
#pragma HLS INTERFACE s_axilite port=Cout  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=kernel bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

    if (cols > MAX_WIDTH) return;

    // Local kernel
    data_t local_kernel[MAX_COUT][MAX_CIN][K*K];
#pragma HLS ARRAY_PARTITION variable=local_kernel complete dim=3
#pragma HLS ARRAY_PARTITION variable=local_kernel complete dim=2

LOAD_KERNEL:
    for (int oc = 0; oc < Cout; oc++) {
        for (int ic = 0; ic < Cin; ic++) {
//#pragma HLS PIPELINE II=1
            for (int k = 0; k < K*K; k++) {
                local_kernel[oc][ic][k] = kernel[oc][ic][k];
            }
        }
    }

    int padded_cols = cols + 2*PAD;
    int padded_rows = rows + 2*PAD;

    // Line buffers per channel
    data_t line_buf[MAX_CIN][K-1][MAX_WIDTH + 2*PAD];
#pragma HLS ARRAY_PARTITION variable=line_buf complete dim=1
#pragma HLS ARRAY_PARTITION variable=line_buf complete dim=2

    // Window per channel
    data_t window[MAX_CIN][K][K];
#pragma HLS ARRAY_PARTITION variable=window complete dim=2
#pragma HLS ARRAY_PARTITION variable=window complete dim=3

    // Init
INIT:
    for (int ic = 0; ic < Cin; ic++) {
        for (int j = 0; j < MAX_WIDTH + 2*PAD; j++) {
#pragma HLS PIPELINE II=1
            line_buf[ic][0][j] = 0;
            line_buf[ic][1][j] = 0;
        }
    }

    // Main loops
ROW_LOOP:
    for (int pi = 0; pi < padded_rows; pi++) {
#pragma HLS LOOP_TRIPCOUNT min=66 max=66 avg=66
    COL_LOOP:
        for (int pj = 0; pj < padded_cols; pj++) {
#pragma HLS LOOP_TRIPCOUNT min=66 max=66 avg=66

//#pragma HLS PIPELINE II=1

            data_t in_pix[MAX_CIN];

            // Read all channels
        READ_CHANNELS:
            for (int ic = 0; ic < Cin; ic++) {
#pragma HLS UNROLL
                int real_i = pi - PAD;
                int real_j = pj - PAD;

                bool valid = (real_i >= 0 && real_i < rows &&
                              real_j >= 0 && real_j < cols);

                if (valid) {
                    axis_pkt_t pkt = in_stream.read();
                    in_pix[ic] = unpack(pkt.data);
                } else {
                    in_pix[ic] = 0;
                }
            }

            // Update window per channel
        UPDATE_WINDOW:
            for (int ic = 0; ic < Cin; ic++) {
#pragma HLS UNROLL

                for (int r = 0; r < K; r++) {
                    window[ic][r][0] = window[ic][r][1];
                    window[ic][r][1] = window[ic][r][2];
                }

                window[ic][0][K-1] = line_buf[ic][0][pj];
                window[ic][1][K-1] = line_buf[ic][1][pj];
                window[ic][2][K-1] = in_pix[ic];

                line_buf[ic][0][pj] = line_buf[ic][1][pj];
                line_buf[ic][1][pj] = in_pix[ic];
            }

            // Compute outputs
        COMPUTE_OUTPUT:
            for (int oc = 0; oc < Cout; oc++) {
#pragma HLS PIPELINE II=1

                data_t acc = 0;

                for (int ic = 0; ic < Cin; ic++) {
#pragma HLS UNROLL
                    for (int r = 0; r < K; r++) {
#pragma HLS UNROLL
                        for (int c = 0; c < K; c++) {
#pragma HLS UNROLL
                            acc += window[ic][r][c] *
                                   local_kernel[oc][ic][r*K+c];
                        }
                    }
                }

                int out_i = pi - (K-1);
                int out_j = pj - (K-1);

                bool valid_out = (out_i >= 0 && out_i < rows &&
                                  out_j >= 0 && out_j < cols);

                if (valid_out) {
                    int idx = (out_i * cols + out_j) * Cout + oc;
                    bool last = (idx == rows*cols*Cout - 1);

                    axis_pkt_t out_pkt;
                    out_pkt.data = pack(acc);
                    out_pkt.keep = -1;
                    out_pkt.last = last;
                    out_stream.write(out_pkt);
                }
            }
        }
    }
}
