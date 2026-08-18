#include "fir_stream.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SAMPLES 512
#define TOLERANCE   1e-4f

static float absf(float x) { return x < 0 ? -x : x; }

static int read_vector(const char *fname, float *buf, int max_n) {
    FILE *f = fopen(fname, "r");
    if (!f) { fprintf(stderr, "Cannot open %s\n", fname); exit(1); }
    int n = 0;
    while (n < max_n && fscanf(f, "%f", &buf[n]) == 1) n++;
    fclose(f);
    return n;
}

int main()
{
    float input[MAX_SAMPLES], expected[MAX_SAMPLES];

    int n_in  = read_vector("../input.txt",           input,    MAX_SAMPLES);
    int n_exp = read_vector("../expected_output.txt",  expected, MAX_SAMPLES);
    if (n_in != n_exp || n_in == 0) {
        printf("FAIL: mismatched vector lengths (%d vs %d)\n", n_in, n_exp);
        return 1;
    }

    /* Set up HLS streams */
    hls::stream<axis_pkt_t> in_stream("in");
    hls::stream<axis_pkt_t> out_stream("out");

    /* Pack input into AXI-Stream packets */
    union { float f; unsigned u; } conv;
    for (int i = 0; i < n_in; i++) {
        axis_pkt_t pkt;
        conv.f = input[i];
        pkt.data = (ap_int<32>)conv.u;
        pkt.keep = -1;
        pkt.strb = -1;
        pkt.user = 0;
        pkt.id   = 0;
        pkt.dest = 0;
        pkt.last = (i == n_in - 1) ? 1 : 0;
        in_stream.write(pkt);
    }

    /* Run the DUT */
    fir_stream(in_stream, out_stream, n_in);

    /* Verify */
    int errors = 0;
    for (int i = 0; i < n_in; i++) {
        axis_pkt_t pkt = out_stream.read();
        conv.u = (unsigned)(ap_uint<32>)pkt.data;
        float y = conv.f;
        float err = absf(y - expected[i]);
        if (err > TOLERANCE) {
            printf("MISMATCH at sample %d: got %.6f, expected %.6f (err=%.6e)\n",
                   i, y, expected[i], err);
            errors++;
        }
    }

    if (errors == 0)
        printf("PASS: %d samples matched (tolerance=%.0e)\n", n_in, TOLERANCE);
    else
        printf("FAIL: %d / %d mismatches\n", errors, n_in);

    return errors ? 1 : 0;
}
