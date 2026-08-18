#include <iostream>
#include <iomanip>
#include "2DCONV_stream.h" // This brings in fir_common.h and data_t

int main() {
    const int ROWS = 128;
    const int COLS = 128;
    const int K = 3;

    // ─────────────────────────────────────────────
    // Kernel (Adjusted to fit ap_fixed<16, 3>)
    // Range is approximately [-4.0 to 3.999]
    // ─────────────────────────────────────────────
    data_t kernel[K*K] = {
        -0.25, -0.25, -0.25,
        -0.25,  2.0,  -0.25,
        -0.25, -0.25, -0.25
    };

    hls::stream<axis_pkt_t> in_stream("input_stream");
    hls::stream<axis_pkt_t> out_stream("output_stream");

    // ─────────────────────────────────────────────
    // Input Image
    // ─────────────────────────────────────────────
    data_t image_in[ROWS][COLS] = {0}; // Initialize with integer 0

    for(int r = 2; r < 6; r++) {
        for(int c = 2; c < 6; c++) {
            image_in[r][c] = 1;
        }
    }

    // ─────────────────────────────────────────────
    // Send input stream (Using bit-ranges for packing)
    // ─────────────────────────────────────────────
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            axis_pkt_t pkt;

            // Map the 16 bits of the fixed-point number into the lower 16 bits of the stream
            pkt.data.range(15, 0) = image_in[i][j].range();
            pkt.data.range(31, 16) = 0; // Zero out upper bits for safety

            pkt.keep = -1;
            pkt.last = ((i == ROWS-1) && (j == COLS-1)) ? 1 : 0;

            in_stream.write(pkt);
        }
    }

    std::cout << "Starting C Simulation...\n";

    // ─────────────────────────────────────────────
    // Run HLS
    // ─────────────────────────────────────────────
    conv2d_stream(in_stream, out_stream, ROWS, COLS, kernel);

    // ─────────────────────────────────────────────
    // Read output (NO OFFSET)
    // ─────────────────────────────────────────────
    data_t image_out_hw[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            axis_pkt_t pkt = out_stream.read();
            data_t val;

            // Extract the lower 16 bits back into the fixed-point type
            val.range() = pkt.data.range(15, 0);
            image_out_hw[i][j] = val;
        }
    }

    // ─────────────────────────────────────────────
    // SW Golden (ZERO PADDING)
    // ─────────────────────────────────────────────
    data_t expected_out[ROWS][COLS] = {0};

    // Use the exact same wide accumulator type as the hardware
    // to guarantee a bit-exact match during simulation
    typedef ap_fixed<32, 10> acc_t;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {

            acc_t acc = 0;

            for (int kr = 0; kr < K; kr++) {
                for (int kc = 0; kc < K; kc++) {

                    int rr = r + kr - 1;
                    int cc = c + kc - 1;

                    if (rr >= 0 && rr < ROWS &&
                        cc >= 0 && cc < COLS) {

                        acc += (acc_t)image_in[rr][cc] * (acc_t)kernel[kr*K + kc];
                    }
                }
            }

            // Truncate back down to the 16-bit output size, just like hardware
            expected_out[r][c] = (data_t)acc;
        }
    }

    // ─────────────────────────────────────────────
    // Validation
    // ─────────────────────────────────────────────
    int errors = 0;

    std::cout << "Validating FULL image (zero padding)...\n";

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {

            data_t hw_val = image_out_hw[r][c];
            data_t sw_val = expected_out[r][c];

            // Because HLS C Simulation is bit-accurate for fixed-point,
            // we can check for absolute equality instead of using a tolerance threshold.
            if (hw_val != sw_val) {
                std::cout << "Mismatch at (" << r << "," << c << "): "
                          << "HW=" << hw_val.to_double()
                          << " SW=" << sw_val.to_double() << "\n";
                errors++;
            }
        }
    }

    // ─────────────────────────────────────────────
    // Result
    // ─────────────────────────────────────────────
    std::cout << "\n========== RESULT ==========\n";

    if (errors == 0) {
        std::cout << "SUCCESS: HW matches SW (zero padding)!\n";
        return 0;
    } else {
        std::cout << "FAILED: " << errors << " mismatches\n";
        return 1;
    }
}
