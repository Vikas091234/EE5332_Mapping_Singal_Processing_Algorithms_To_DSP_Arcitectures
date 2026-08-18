#include "fir_stream.h"

/* ---------- float <-> ap_int<32> conversion ---------- */
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

/* ---------- Streaming FIR ---------- */
void fir_stream(hls::stream<axis_pkt_t> &in_stream,
                hls::stream<axis_pkt_t> &out_stream,
                int n)
{
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream
#pragma HLS INTERFACE s_axilite port=n
#pragma HLS INTERFACE s_axilite port=return

    static data_t shift_reg[N_TAPS] = {0};

    sample_loop:
    for (int i = 0; i < n; i++) {

        /* Read input sample */
        axis_pkt_t in_pkt = in_stream.read();
        data_t x = unpack(in_pkt.data);

        /* Shift register */
        shift_loop:
        for (int j = N_TAPS - 1; j > 0; j--) {
            shift_reg[j] = shift_reg[j - 1];
        }
        shift_reg[0] = x;

        /* FIR multiply-accumulate */
        data_t acc = 0;
        mac_loop:
        for (int j = 0; j < N_TAPS; j++) {
            acc += coeffs[j] * shift_reg[j];
        }

        /* Write output sample */
        axis_pkt_t out_pkt;
        out_pkt.data = pack(acc);
        out_pkt.keep = -1;       /* all bytes valid */
        out_pkt.strb = -1;
        out_pkt.user = 0;
        out_pkt.id   = 0;
        out_pkt.dest = 0;
        out_pkt.last = (i == n - 1) ? 1 : 0;

        out_stream.write(out_pkt);
    }
}

