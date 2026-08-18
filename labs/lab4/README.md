# Lab 4 - FIR filter synthesis

This is a more practical version of the Vitis HLS synthesis.  The filter synthesized here will be implemented on the board later.

## Solutions

Generate at least 3 solutions: the minimum required are the following.

1. Default synthesis without directives.
2. Add directives as required to get it working with II=1 and get the maximum operating frequency.
3. Constraint of maximum 2 multipliers.

For all the designs, also add `INTERFACE` directives so that the input and output are of type `AXI Stream`.  As discussed in class, this means there will be a `VALID` and `READY` signal along with the data.  We will later use this to push data into the filter and get the results out.

## Submission

- Directive files
- Synthesis reports
- Single PDF with analysis

Create a zip file in the same way as the previous assignments and submit.
