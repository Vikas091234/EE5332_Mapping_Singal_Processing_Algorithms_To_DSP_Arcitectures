#include "2DCONV_stream.h"

#define MAX_ROWS 128
#define MAX_COLS 128
#define K 3

// --------------------------------------------------
// Baseline 2D Convolution
// - Float implementation
// - No pragmas
// - No AXI streams
// - No line buffers
// - No sliding window optimization
// - Pure software-style nested loops
// --------------------------------------------------

void conv2d_baseline(
    float input[MAX_ROWS][MAX_COLS],
    float output[MAX_ROWS][MAX_COLS],
    float kernel[K][K],
    int rows,
    int cols)
{
    // Traverse output image
    for(int i = 0; i < rows; i++) {

        for(int j = 0; j < cols; j++) {

            float acc = 0.0f;

            // Convolution kernel
            for(int ki = 0; ki < K; ki++) {

                for(int kj = 0; kj < K; kj++) {

                    // Input coordinates
                    int r = i + ki - (K / 2);
                    int c = j + kj - (K / 2);

                    // Boundary check (zero padding)
                    if(r >= 0 && r < rows &&
                       c >= 0 && c < cols) {

                        acc += input[r][c] * kernel[ki][kj];
                    }
                }
            }

            output[i][j] = acc;
        }
    }
}