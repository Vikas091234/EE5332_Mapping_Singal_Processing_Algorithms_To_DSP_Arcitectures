# Verilog coding examples 

There are 4 pairs of (System)Verilog files here: each consists of a test bench as well as an empty module as a placeholder for the design under test.

You need to fill in the Verilog code in the corresponding files, and ensure that they all pass the tests using the `iverilog` simulator (this is what will be used for testing and was used on EDAplayground).

The command that will be used for compiling and running is (for example):

```bash
iverilog -g2012 counter.sv tb_counter.sv
./a.out 
```

The above commands first compile the `counter` module and the corresponding test bench, and then execute the resulting program.  As it is, all the tests will fail, but once you put in the correct counter code you should be able to make all tests pass.

## Submission

Submit the files on Moodle.  You should submit a single file with the name `rollno.zip`.  

- This file should contain a single folder called `lab1`, which in turn contains only 4 `.sv` files.  
- Do not submit the test benches or the README file.  
- Ensure that there are no extra files like `.DS_store` or `.Trash` or anything else other than the required files.
- The files should retain their names as given here - do not change them in any way.

Note that any errors in submission format will result in your submission being rejected and you will have to submit again.  This is important, since following exact instructions is essential for us to be able to grade the assignments.

