# Lab 3 - HLS basics

This lab is to test the basic implementation of directives in Vitis HLS.  You are given the code that was used to demonstrate the differential equation example in class.  You need to apply (at least) 3 sets of directives, and generate the synthesis report from each.  Finally, submit a report that contains your analysis of the problem.

## Experiments

Set up a project to implement Vitis HLS synthesis for the differential equation solver.  For the target FPGA, use the Zynq FPGA available in class (not the default Artix that was used in the class demo). 

Create 3 solutions:

1. Default: no directives applied.  Just the basic C function.
2. Turn off pipelining and set a constraint on the number of multipliers to 1.
3. Set the initiation interval to 1 and relax the timing constraint to 50ns.

Run the synthesis and get the reports (`csynth.rpt`) for each solution.

## Submission

Create a folder named `lab3/` with the following contents:

- `directive.tcl` for each of the designs (name them `directive1.tcl`, `directive2.tcl` etc.)
- `csynth1.rpt`, `csynth2.rpt` etc: one for each solution.
- `lab3.pdf`: A single PDF file (not more than 2 pages) that summarizes your findings: what settings were needed to get the solutions.  

Create a single zip file named `rollno.zip` (replace `rollno` with your roll number in lower case).  When the file is unzipped, it should directly contain the `lab3` folder under it.
