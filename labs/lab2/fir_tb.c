#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fir.h"

#define MAX_SAMPLES 2048
#define TOLERANCE 1e-5f

static int read_vector(const char *path, data_t *buffer, int max_samples)
{
    FILE *file_obj = fopen(path, "r");
    int count = 0;

    if (file_obj == NULL) {
        fprintf(stderr, "Could not open %s\n", path);
        return -1;
    }

    while (count < max_samples && fscanf(file_obj, "%f", &buffer[count]) == 1) {
        count++;
    }

    fclose(file_obj);
    return count;
}

int main(void)
{
    data_t input[MAX_SAMPLES];
    data_t expected[MAX_SAMPLES];
    int input_count;
    int expected_count;
    int index;
    int failures = 0;

    input_count = read_vector("input.txt", input, MAX_SAMPLES);
    expected_count = read_vector("expected_output.txt", expected, MAX_SAMPLES);

    if (input_count < 0 || expected_count < 0) {
        return 1;
    }
    if (input_count != expected_count) {
        fprintf(stderr, "Length mismatch: input=%d expected=%d\n", input_count, expected_count);
        return 1;
    }

    for (index = 0; index < input_count; index++) {
        data_t y_c = fir_filter_sample(input[index]);
        data_t error = fabsf(y_c - expected[index]);

        if (error > TOLERANCE) {
            if (failures < 10) {
                printf(
                    "Mismatch at n=%d: C=%0.9f expected=%0.9f error=%0.9f\n",
                    index,
                    y_c,
                    expected[index],
                    error
                );
            }
            failures++;
        }
    }

    if (failures == 0) {
        printf("PASS: %d samples matched (tolerance=%g)\n", input_count, TOLERANCE);
        return 0;
    }

    printf("FAIL: %d mismatches out of %d samples\n", failures, input_count);
    return 1;
}
