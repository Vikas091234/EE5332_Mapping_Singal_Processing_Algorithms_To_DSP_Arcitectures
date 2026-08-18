#include "fir.h"

data_t fir_filter_sample(data_t x_in)
{
    static data_t shift_reg[N_TAPS] = {0};
    data_t acc = 0.0f;
    int index;
#pragma HLS PIPELINE II=2
#pragma HLS ALLOCATION operation instances=mul limit=6
#pragma HLS INTERFACE mode=s_axilite port=return
    for (index = N_TAPS - 1; index > 0; index--) {
        shift_reg[index] = shift_reg[index - 1];
    }
    shift_reg[0] = x_in;

    for (index = 0; index < N_TAPS; index++) {
        acc += (data_t)fir_coeffs[index] * shift_reg[index];
    }

    return acc;
}
