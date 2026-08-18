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
    // Traverse image rows
    for(int i = 0; i < rows; i++) {

        // Traverse image columns
        for(int j = 0; j < cols; j++) {

#pragma HLS PIPELINE  II= 6

            // Accumulator
            data_t acc = 0;

            // Kernel traversal
            for(int ki = 0; ki < K; ki++) {
#pragma HLS UNROLL
                for(int kj = 0; kj < K; kj++) {
#pragma HLS UNROLL
                    // Neighbor coordinates
                    int r = i + ki - (K / 2);
                    int c = j + kj - (K / 2);

                    // Boundary check (zero padding)
                    if(r >= 0 && r < rows &&
                       c >= 0 && c < cols) {

                        acc += input[r][c] * kernel[ki][kj];
                    }
                }
            }

            // Store result
            output[i][j] = acc;
        }
    }
}
