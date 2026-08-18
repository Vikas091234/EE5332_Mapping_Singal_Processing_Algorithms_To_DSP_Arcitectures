#include <iostream>
#include <iomanip>

#define MAX_ROWS 128
#define MAX_COLS 128
#define K 3

using namespace std;

// --------------------------------------------------
// Function Prototype
// --------------------------------------------------

void conv2d_baseline(
    float input[MAX_ROWS][MAX_COLS],
    float output[MAX_ROWS][MAX_COLS],
    float kernel[K][K],
    int rows,
    int cols
);

// --------------------------------------------------
// Main Testbench
// --------------------------------------------------

int main()
{
    // --------------------------------------------------
    // Test Image
    // --------------------------------------------------

    const int rows = 4;
    const int cols = 4;

    float input[MAX_ROWS][MAX_COLS] = {

        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    // --------------------------------------------------
    // Output Buffer
    // --------------------------------------------------

    float output[MAX_ROWS][MAX_COLS] = {0};

    // --------------------------------------------------
    // 3x3 Kernel
    // --------------------------------------------------

    float kernel[K][K] = {

        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    // --------------------------------------------------
    // Run Convolution
    // --------------------------------------------------

    conv2d_baseline(
        input,
        output,
        kernel,
        rows,
        cols
    );

    // --------------------------------------------------
    // Print Input Image
    // --------------------------------------------------

    cout << "\nInput Image:\n";

    for(int i = 0; i < rows; i++) {

        for(int j = 0; j < cols; j++) {

            cout << setw(6)
                 << input[i][j];
        }

        cout << endl;
    }

    // --------------------------------------------------
    // Print Kernel
    // --------------------------------------------------

    cout << "\nKernel:\n";

    for(int i = 0; i < K; i++) {

        for(int j = 0; j < K; j++) {

            cout << setw(6)
                 << kernel[i][j];
        }

        cout << endl;
    }

    // --------------------------------------------------
    // Print Output
    // --------------------------------------------------

    cout << "\nOutput Image:\n";

    for(int i = 0; i < rows; i++) {

        for(int j = 0; j < cols; j++) {

            cout << setw(8)
                 << output[i][j];
        }

        cout << endl;
    }

    return 0;
}