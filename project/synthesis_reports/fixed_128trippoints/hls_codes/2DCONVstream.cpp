#include "2DCONV_stream.h"
#include <hls_stream.h>

#define MAX_WIDTH 256
#define K 3

// --------------------------------------------------
// Float <-> AXI packet conversion
// --------------------------------------------------

union float_bits {
    float    f;
    unsigned u;
};

static inline data_t unpack(ap_int<32> raw) {
#ifdef USE_FIXED
    data_t val;
    val.range() = raw.range(DATA_WIDTH - 1, 0);
    return val;
#else
    float_bits fb;
    fb.u = (unsigned)raw;
    return fb.f;
#endif
}

static inline ap_int<32> pack(data_t val) {
#ifdef USE_FIXED
    ap_int<32> raw = 0;
    raw.range(DATA_WIDTH - 1, 0) = val.range();
    return raw;
#else
    float_bits fb;
    fb.f = val;
    return (ap_int<32>)fb.u;
#endif
}

// --------------------------------------------------
// Optimized Streaming 2D Convolution
//
// Improvements over baseline:
// 1. AXI Streaming
// 2. Sliding Window
// 3. Line Buffers
// 4. Pipeline
// 5. Loop Unrolling
// 6. Array Partitioning
// --------------------------------------------------

void conv2d_optimized(
    hls::stream<axis_pkt_t> &in_stream,
    hls::stream<axis_pkt_t> &out_stream,
    int rows,
    int cols,
    data_t kernel[K*K]
)
{

// --------------------------------------------------
// AXI Interfaces
// --------------------------------------------------

#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream

#pragma HLS INTERFACE s_axilite port=rows
#pragma HLS INTERFACE s_axilite port=cols
#pragma HLS INTERFACE s_axilite port=kernel
#pragma HLS INTERFACE s_axilite port=return

// --------------------------------------------------
// Local Kernel Storage
// --------------------------------------------------

    data_t local_kernel[K*K];

#pragma HLS ARRAY_PARTITION variable=local_kernel complete dim=1

// --------------------------------------------------
// Load Kernel Once
// --------------------------------------------------

LOAD_KERNEL:
    for(int i = 0; i < K*K; i++) {

#pragma HLS PIPELINE II=1

        local_kernel[i] = kernel[i];
    }

// --------------------------------------------------
// Line Buffers
// Store Previous Rows
// --------------------------------------------------

    static data_t line_buf[K-1][MAX_WIDTH];

#pragma HLS ARRAY_PARTITION variable=line_buf complete dim=1

// --------------------------------------------------
// Sliding Window
// --------------------------------------------------

    data_t window[K][K];

#pragma HLS ARRAY_PARTITION variable=window complete dim=0

// --------------------------------------------------
// Main Pixel Processing
// --------------------------------------------------

ROW_LOOP:
    for(int i = 0; i < rows; i++) {
#pragma HLS LOOP_TRIPCOUNT min=128 max=128
    COL_LOOP:
        for(int j = 0; j < cols; j++) {
#pragma HLS LOOP_TRIPCOUNT min=128 max=128
#pragma HLS PIPELINE II=1

// --------------------------------------------------
// Read Incoming Pixel
// --------------------------------------------------

            axis_pkt_t in_pkt = in_stream.read();

            data_t new_pixel = unpack(in_pkt.data);

// --------------------------------------------------
// Shift Window Left
// --------------------------------------------------

        SHIFT_ROWS:
            for(int r = 0; r < K; r++) {

#pragma HLS UNROLL

            SHIFT_COLS:
                for(int c = 0; c < K-1; c++) {

#pragma HLS UNROLL

                    window[r][c] = window[r][c+1];
                }
            }

// --------------------------------------------------
// Insert New Rightmost Column
// --------------------------------------------------

            window[0][K-1] = line_buf[0][j];
            window[1][K-1] = line_buf[1][j];
            window[2][K-1] = new_pixel;

// --------------------------------------------------
// Update Line Buffers
// --------------------------------------------------

            line_buf[0][j] = line_buf[1][j];
            line_buf[1][j] = new_pixel;

// --------------------------------------------------
// Convolution MAC
// --------------------------------------------------

            data_t acc = 0;
            if (i >=K-1 && j>=K-1)
            {
            MAC_ROW:
            for(int r = 0; r < K; r++) {

            #pragma HLS UNROLL
                
            MAC_COL:
                for(int c = 0; c < K; c++) {

            #pragma HLS UNROLL

                    acc += window[r][c]* local_kernel[r*K + c];
                  }
                }
            }

// --------------------------------------------------
// Output Result
// --------------------------------------------------

            axis_pkt_t out_pkt;

            out_pkt.data = pack(acc);

            out_pkt.keep = -1;

            out_pkt.last =
                ((i == rows-1) &&
                 (j == cols-1)) ? 1 : 0;

            out_stream.write(out_pkt);
        }
    }
}
