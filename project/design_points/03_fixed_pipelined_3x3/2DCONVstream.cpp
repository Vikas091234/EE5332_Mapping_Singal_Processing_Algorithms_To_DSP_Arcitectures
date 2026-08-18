#include "2DCONV_stream.h"
#include <hls_stream.h>

#define MAX_WIDTH 128
#define K 3
#define PAD (K/2)   // = 1 for 3x3 kernel

// ── Fixed-Point Pack and Unpack Logic ─────────────────────────────
// Extracts the lower 16 bits from the AXI stream
static inline data_t unpack(ap_int<32> raw) {
    data_t val;
    val.range() = raw.range(15, 0);
    return val;
}

// Maps the 16 fixed-point bits into the lower 16 bits of the AXI packet
static inline ap_int<32> pack(data_t val) {
    ap_int<32> raw = 0;
    raw.range(15, 0) = val.range();
    return raw;
}

// ── Main IP Block ─────────────────────────────────────────────────
void conv2d_stream(hls::stream<axis_pkt_t> &in_stream,
                   hls::stream<axis_pkt_t> &out_stream,
                   int rows, int cols,
                   data_t kernel[K*K]) // Highly recommended to use data_t here!
{
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream
#pragma HLS INTERFACE s_axilite port=rows   bundle=CTRL
#pragma HLS INTERFACE s_axilite port=cols   bundle=CTRL
#pragma HLS INTERFACE s_axilite port=kernel bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

    if (cols > MAX_WIDTH) return;

    // Cache the kernel locally into registers
    data_t local_kernel[K*K];
#pragma HLS ARRAY_PARTITION variable=local_kernel complete dim=1
    for (int i = 0; i < K*K; i++) {
#pragma HLS UNROLL
        local_kernel[i] = kernel[i];
    }

    // Line buffers sized for padded width
    int padded_cols = cols + 2*PAD;
    data_t line_buf[K-1][MAX_WIDTH + 2*PAD];
#pragma HLS ARRAY_PARTITION variable=line_buf complete dim=1

    data_t window[K][K];
#pragma HLS ARRAY_PARTITION variable=window complete dim=0

    // Zero everything (Using integer 0, NOT 0.0f)
    for (int j = 0; j < MAX_WIDTH + 2*PAD; j++) {
#pragma HLS PIPELINE II=1
        line_buf[0][j] = 0;
        line_buf[1][j] = 0;
    }
    for (int r = 0; r < K; r++)
        for (int c = 0; c < K; c++)
            window[r][c] = 0;

    int padded_rows = rows + 2*PAD;

    for (int pi = 0; pi < padded_rows; pi++) {
        for (int pj = 0; pj < padded_cols; pj++) {
#pragma HLS PIPELINE II=1

            // ── Determine pixel value (real or zero pad) ──────────
            int real_i = pi - PAD;
            int real_j = pj - PAD;

            data_t new_pixel = 0; // Initialize with fixed-point 0
            bool in_bounds = (real_i >= 0 && real_i < rows &&
                              real_j >= 0 && real_j < cols);
            if (in_bounds) {
                axis_pkt_t in_pkt = in_stream.read();
                new_pixel = unpack(in_pkt.data);
            }

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

            // Left-column border zeroing
            if (pj == 0) {
                for (int r = 0; r < K; r++) {
                    window[r][0] = 0;
                    window[r][1] = 0;
                }
            } else if (pj == 1) {
                for (int r = 0; r < K; r++)
                    window[r][0] = 0;
            }

            // ── MAC (Multiply-Accumulate) ─────────────────────────
            // Wide accumulator to prevent bit-overflow during summing
            typedef ap_fixed<32, 10> acc_t;
            acc_t acc = 0;

            for (int r = 0; r < K; r++) {
#pragma HLS UNROLL
                for (int c = 0; c < K; c++) {
#pragma HLS UNROLL
                    acc += window[r][c] * local_kernel[r * K + c];
            }}

            // ── Write Output ──────────────────────────────────────
            int out_i = pi - (K-1);
            int out_j = pj - (K-1);
            bool valid_out = (out_i >= 0 && out_i < rows &&
                              out_j >= 0 && out_j < cols);

            if (valid_out) {
                int out_linear = out_i * cols + out_j;
                bool is_last   = (out_linear == rows * cols - 1);

                // Cast wide accumulator back to standard data_t (16,3)
                data_t final_pixel = (data_t)acc;

                axis_pkt_t out_pkt;
                out_pkt.data = pack(final_pixel);
                out_pkt.keep = -1;
                out_pkt.strb = -1;  // mark all bytes valid for DMA S2MM
                out_pkt.last = is_last ? 1 : 0;
                out_stream.write(out_pkt);
            }
        }
    }
}
