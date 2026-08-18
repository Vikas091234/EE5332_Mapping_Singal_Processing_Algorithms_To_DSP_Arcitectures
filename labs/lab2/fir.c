#include "fir.h"

// Static buffer to hold previous samples 
// N_TAPS is defined in the auto-generated fir_coeffs.h
static data_t shift_reg[N_TAPS] = {0};

data_t fir_filter_sample(data_t x_in)
{
    data_t y_out = 0;
    int i;

    // 1. Shift the delay line and insert the new sample at the beginning
    for (i = N_TAPS - 1; i > 0; i--) {
        shift_reg[i] = shift_reg[i - 1];
    }
    shift_reg[0] = x_in;

    // y[n] = sum(h[i] * x[n-i])
    for (i = 0; i < N_TAPS; i++) {
        y_out += fir_coeffs[i] * shift_reg[i];
    }

    return y_out;
}