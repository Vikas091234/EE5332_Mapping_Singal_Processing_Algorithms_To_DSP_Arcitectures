# Lab 2: FIR Filter C Test Bench

This lab uses Python to generate FIR coefficients and test vectors, then uses C
to run the FIR filter and check results.

## Files

- `generate_fir_test_vectors.py`: designs a 51-tap low-pass FIR (windowed-sinc + Hamming)
- `fir.c` and `fir.h`: FIR filter implementation with internal static filter state
- `fir_tb.c`: simple test bench that compares C output to Python reference

### Auto-generated 

The files below are generated when you run `generate_fir_test_vectors.py`.  You can try changing that file and seeing the different coefficient sets that are generated.

- `fir_coeffs.h`: auto-generated coefficients for the C code
- `input.txt`: auto-generated input sequence
- `expected_output.txt`: auto-generated reference output from Python

## Run

1. Generate vectors:

   ```bash
   python3 generate_fir_test_vectors.py
   ```

2. Build and run test bench:

   ```bash
   make test
   ```

A successful run prints `PASS`.

## Assignment and Submission 

The file `fir.c` is incomplete.  Write code to actually do the filtering such that it passes the test run by `fir_tb.c`.

Zip the resulting files into a single `.zip` file named as `rollno.zip` - all letters in lower case.  For example `ee12b345.zip`.  The zip file should contain a single folder named `lab2`, inside which you should have the same set of files as given originally.

Your `fir.c` file should have brief comments explaining the approach taken to implementing the filter.

Submit the zip file on Moodle.
