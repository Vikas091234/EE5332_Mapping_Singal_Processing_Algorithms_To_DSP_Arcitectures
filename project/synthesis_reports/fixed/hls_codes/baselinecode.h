#ifndef _BASELINE_CONV_H_
#define _BASELINE_CONV_H_

// Using standard defines to match your array sizes
#define MAX_ROWS 128
#define MAX_COLS 128
#define K 3

/* * We use extern "C" to ensure the C++ compiler doesn't "mangle" the name.
 * This allows the testbench to link with baselinecode.cpp regardless of
 * whether they are compiled as C or C++.
 */
extern "C" {
    void conv2d_baseline(
        float input[MAX_ROWS][MAX_COLS],
        float output[MAX_ROWS][MAX_COLS],
        float kernel[K][K],
        int rows,
        int cols
    );
}

#endif