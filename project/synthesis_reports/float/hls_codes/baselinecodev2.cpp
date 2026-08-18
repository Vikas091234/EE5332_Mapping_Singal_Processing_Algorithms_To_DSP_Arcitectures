#include "2DCONV_stream.h"
#include <iostream>
#include <iomanip>
#define MAX_ROWS 128
#define MAX_COLS 128
#define K 3

// --------------------------------------------------
// Baseline 2D Convolution
// Uses datatype selected in 2DCONV_stream.h
//
// If USE_FIXED is defined:
//     data_t = ap_fixed<...>
//
// Otherwise:
//     data_t = float
//
// Same source supports both float and fixed-point
// --------------------------------------------------

void conv2d_baseline(
    data_t input[MAX_ROWS][MAX_COLS],
    data_t output[MAX_ROWS][MAX_COLS],
    data_t kernel[K][K],
    int rows,
    int cols)
{

// --------------------------------------------------
// Local Kernel Registers
// --------------------------------------------------

    data_t local_kernel[K][K];

#pragma HLS ARRAY_PARTITION variable=local_kernel complete dim=0

LOAD_KERNEL:
    for(int i = 0; i < K; i++) {

        for(int j = 0; j < K; j++) {

#pragma HLS PIPELINE II=1

            local_kernel[i][j] = kernel[i][j];
        }
    }

// --------------------------------------------------
// Main Convolution
// --------------------------------------------------

ROW_LOOP:
    for(int i = 0; i < rows; i++) {

#pragma HLS LOOP_TRIPCOUNT min=128 max=128

    COL_LOOP:
        for(int j = 0; j < cols; j++) {

#pragma HLS LOOP_TRIPCOUNT min=128 max=128
#pragma HLS PIPELINE II=1

// --------------------------------------------------
// Local Window Buffer
// --------------------------------------------------

            data_t window[K][K];

#pragma HLS ARRAY_PARTITION variable=window complete dim=0

// --------------------------------------------------
// Load Local Window
// --------------------------------------------------

        LOAD_WINDOW_ROW:
            for(int ki = 0; ki < K; ki++) {

#pragma HLS UNROLL

            LOAD_WINDOW_COL:
                for(int kj = 0; kj < K; kj++) {

#pragma HLS UNROLL

                    int r = i + ki - (K/2);
                    int c = j + kj - (K/2);

                    if(r >= 0 && r < rows &&
                       c >= 0 && c < cols) {

                        window[ki][kj] = input[r][c];
                    }
                    else {

                        window[ki][kj] = 0;
                    }
                }
            }

// --------------------------------------------------
// Parallel MAC
// --------------------------------------------------

            data_t acc = 0;

        MAC_ROW:
            for(int ki = 0; ki < K; ki++) {

#pragma HLS UNROLL

            MAC_COL:
                for(int kj = 0; kj < K; kj++) {

#pragma HLS UNROLL

                    acc += window[ki][kj] *
                           local_kernel[ki][kj];
                }
            }

// --------------------------------------------------
// Store Output
// --------------------------------------------------

            output[i][j] = acc;
        }
    }
}