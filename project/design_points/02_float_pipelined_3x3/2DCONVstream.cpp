#include "2DCONV_stream.h"
#include <hls_stream.h>

#define MAX_WIDTH 128
#define K 3
#define PAD (K/2)   // = 1 for 3x3 kernel

union float_bits { float f; unsigned u; };

static inline data_t unpack(ap_int<32> raw) {
    float_bits fb; fb.u = (unsigned)raw; return fb.f;
}
static inline ap_int<32> pack(data_t val) {
    float_bits fb; fb.f = val; return (ap_int<32>)fb.u;
}

void conv2d_stream(hls::stream<axis_pkt_t> &in_stream,
                   hls::stream<axis_pkt_t> &out_stream,
                   int rows, int cols,
                   data_t kernel[K*K])
{
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream
#pragma HLS INTERFACE s_axilite port=rows   bundle=CTRL
#pragma HLS INTERFACE s_axilite port=cols   bundle=CTRL
#pragma HLS INTERFACE s_axilite port=kernel bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

    if (cols > MAX_WIDTH) return;

    data_t local_kernel[K*K];
#pragma HLS ARRAY_PARTITION variable=local_kernel complete dim=1
    for (int i = 0; i < K*K; i++) {
#pragma HLS PIPELINE II=1
        local_kernel[i] = kernel[i];
    }

    // Line buffers sized for padded width
    int padded_cols = cols + 2*PAD;   // = cols+2 for 3x3
    data_t line_buf[K-1][MAX_WIDTH + 2*PAD];
#pragma HLS ARRAY_PARTITION variable=line_buf complete dim=1

    data_t window[K][K];
#pragma HLS ARRAY_PARTITION variable=window complete dim=0

    // Zero everything
    for (int j = 0; j < MAX_WIDTH + 2*PAD; j++) {
#pragma HLS PIPELINE II=1
        line_buf[0][j] = 0.0f;
        line_buf[1][j] = 0.0f;
    }
    for (int r = 0; r < K; r++)
        for (int c = 0; c < K; c++)
            window[r][c] = 0.0f;

    // ── Iterate over PADDED image: (rows+2*PAD) x (cols+2*PAD) ──
    // Padded row indices:  0..PAD-1 = top zeros
    //                      PAD..PAD+rows-1 = real rows
    //                      PAD+rows..rows+2*PAD-1 = bottom zeros
    // Padded col indices:  0..PAD-1 = left zeros
    //                      PAD..PAD+cols-1 = real cols
    //                      PAD+cols..cols+2*PAD-1 = right zeros

    int padded_rows = rows + 2*PAD;

    for (int pi = 0; pi < padded_rows; pi++) {
        for (int pj = 0; pj < padded_cols; pj++) {
#pragma HLS PIPELINE II=1

            // ── Determine pixel value (real or zero pad) ──────────
            int real_i = pi - PAD;   // row index in original image
            int real_j = pj - PAD;   // col index in original image

            data_t new_pixel = 0.0f;
            bool in_bounds = (real_i >= 0 && real_i < rows &&
                              real_j >= 0 && real_j < cols);
            if (in_bounds) {
                axis_pkt_t in_pkt = in_stream.read();
                new_pixel = unpack(in_pkt.data);
            }
            // out-of-bounds → new_pixel stays 0.0f (matches fillvalue=0)

            // ── Update sliding window ─────────────────────────────
            for (int r = 0; r < K; r++) {
                window[r][0] = window[r][1];
                window[r][1] = window[r][2];
            }

            window[0][K-1] = line_buf[0][pj];
            window[1][K-1] = line_buf[1][pj];
            window[2][K-1] = new_pixel;

            line_buf[0][pj] = line_buf[1][pj];
            line_buf[1][pj] = new_pixel;

            // Left-column border zeroing still needed for padded cols
            if (pj == 0) {
                for (int r = 0; r < K; r++) {
                    window[r][0] = 0.0f;
                    window[r][1] = 0.0f;
                }
            } else if (pj == 1) {
                for (int r = 0; r < K; r++)
                    window[r][0] = 0.0f;
            }

            // ── MAC ───────────────────────────────────────────────
            data_t acc = 0.0f;
            for (int r = 0; r < K; r++) {
#pragma HLS UNROLL
                for (int c = 0; c < K; c++) {
#pragma HLS UNROLL
                    acc += window[r][c] * local_kernel[r * K + c];
            }}

            // ── Write output only for real (unpadded) pixel positions
            // The window at padded position (pi,pj) is centered on
            // (pi-PAD, pj-PAD) in the original image — so output is
            // valid when pi >= PAD+PAD and pj >= PAD+PAD, i.e.,
            // pi >= K-1 and pj >= K-1, which corresponds exactly to
            // real pixel (pi-K+1, pj-K+1) in 0-indexed original image.
            int out_i = pi - (K-1);
            int out_j = pj - (K-1);
            bool valid_out = (out_i >= 0 && out_i < rows &&
                              out_j >= 0 && out_j < cols);

            if (valid_out) {
                int out_linear = out_i * cols + out_j;
                bool is_last   = (out_linear == rows * cols - 1);

                axis_pkt_t out_pkt;
                out_pkt.data = pack(acc);
                out_pkt.keep = -1;
                out_pkt.last = is_last ? 1 : 0;
                out_stream.write(out_pkt);
            }
        }
    }
}
