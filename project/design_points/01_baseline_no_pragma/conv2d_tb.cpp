#include <iostream>
#include <iomanip>
#include <cmath>
#include "2DCONV_stream.h"

union float_bits {
    float f;
    unsigned int u;
};

int main() {
    const int ROWS = 128;
    const int COLS = 128;
    const int K = 3;

    // ─────────────────────────────────────────────
    // Kernel
    // ─────────────────────────────────────────────
    float kernel[K*K] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f,  8.0f, -1.0f,
        -1.0f, -1.0f, -1.0f
    };

    hls::stream<axis_pkt_t> in_stream("input_stream");
    hls::stream<axis_pkt_t> out_stream("output_stream");

    // ─────────────────────────────────────────────
    // Input Image
    // ─────────────────────────────────────────────
    float image_in[ROWS][COLS] = {0.0f};

    for(int r = 2; r < 6; r++) {
        for(int c = 2; c < 6; c++) {
            image_in[r][c] = 1.0f;
        }
    }

    // ─────────────────────────────────────────────
    // Send input stream
    // ─────────────────────────────────────────────
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            axis_pkt_t pkt;
            float_bits fb;

            fb.f = image_in[i][j];
            pkt.data = fb.u;
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
    float image_out_hw[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            axis_pkt_t pkt = out_stream.read();
            float_bits fb;
            fb.u = pkt.data;
            image_out_hw[i][j] = fb.f;
        }
    }

    // ─────────────────────────────────────────────
    // SW Golden (ZERO PADDING)
    // ─────────────────────────────────────────────
    float expected_out[ROWS][COLS] = {0.0f};

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {

            float acc = 0.0f;

            for (int kr = 0; kr < K; kr++) {
                for (int kc = 0; kc < K; kc++) {

                    int rr = r + kr - 1;
                    int cc = c + kc - 1;

                    if (rr >= 0 && rr < ROWS &&
                        cc >= 0 && cc < COLS) {

                        acc += image_in[rr][cc] *
                               kernel[kr*K + kc];
                    }
                }
            }

            expected_out[r][c] = acc;
        }
    }

    // ─────────────────────────────────────────────
    // Validation
    // ─────────────────────────────────────────────
    int errors = 0;

    std::cout << "Validating FULL image (zero padding)...\n";

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {

            float hw_val = image_out_hw[r][c];
            float sw_val = expected_out[r][c];

            float diff = std::fabs(hw_val - sw_val);

            if (diff > 1e-4) {
                std::cout << "Mismatch at (" << r << "," << c << "): "
                          << "HW=" << hw_val
                          << " SW=" << sw_val
                          << " diff=" << diff << "\n";
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
