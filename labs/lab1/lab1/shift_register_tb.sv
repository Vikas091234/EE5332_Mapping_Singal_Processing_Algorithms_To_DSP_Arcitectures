// Shift Register
// Implement an 8-bit shift register with parallel load and serial shift-right.
// This tests understanding of sequential logic and control signal priority.

`timescale 1ns / 1ps

// Test bench
module shift_register_tb();
    logic clk;
    logic rst_n;
    logic load;
    logic shift;
    logic [7:0] d_in;
    logic serial_in;
    logic [7:0] q;
    logic test_passed;
    logic [7:0] expected_q;

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // Instance of student's module
    shift_register dut(
        .clk(clk),
        .rst_n(rst_n),
        .load(load),
        .shift(shift),
        .d_in(d_in),
        .serial_in(serial_in),
        .q(q)
    );

    // Helper task to check output
    task check_output(input string test_name);
        if (q !== expected_q) begin
            $display("Test %s Failed: Expected q=%h, Got q=%h", test_name, expected_q, q);
            test_passed = 1'b0;
        end
    endtask

    initial begin
        test_passed = 1'b1;
        
        // Reset
        rst_n = 0;
        load = 0;
        shift = 0;
        d_in = 8'h00;
        serial_in = 0;
        #20;
        rst_n = 1;
        expected_q = 8'h00;
        check_output("Reset");

        // Test Case 1: Load value
        d_in = 8'hA5;
        load = 1;
        shift = 0;  // Ensure shift doesn't interfere
        #10;
        expected_q = 8'hA5;
        check_output("Load operation");

        // Test Case 2: Verify value holds when both load and shift are 0
        load = 0;
        shift = 0;
        #10;
        check_output("Hold value");

        // Test Case 3: Shift operation when shift=1
        load = 0;
        serial_in = 1;
        shift = 1;
        #10;
        expected_q = 8'hD2;  // A5 >> 1 with serial_in = 1
        check_output("First shift operation");

        // Test Case 4: Multiple shifts
        serial_in = 0;
        #10;
        expected_q = 8'h69;  // D2 >> 1 with serial_in = 0
        check_output("Second shift operation");

        // Test Case 5: Verify no shift occurs when shift=0
        shift = 0;
        serial_in = 1;
        #10;
        check_output("No shift when shift=0");

        // Test Case 6: Load has priority over shift
        load = 1;
        shift = 1;
        d_in = 8'hFF;
        serial_in = 0;
        #10;
        expected_q = 8'hFF;
        check_output("Load priority over shift");

        // Test Case 7: Return to shift operations
        load = 0;
        shift = 1;
        serial_in = 1;
        #10;
        expected_q = 8'hFF;  // FF >> 1 with serial_in = 1
        check_output("Resume shift after load");

        // Test Case 8: Reset during operation
        rst_n = 0;
        #10;
        expected_q = 8'h00;
        check_output("Reset during operation");

        // Test Case 9: Verify reset has priority over load and shift
        rst_n = 0;
        load = 1;
        shift = 1;
        d_in = 8'hAA;
        serial_in = 1;
        #10;
        expected_q = 8'h00;
        check_output("Reset priority");

        if (test_passed)
            $display("PASS");
            
        $finish(0);
    end
endmodule
