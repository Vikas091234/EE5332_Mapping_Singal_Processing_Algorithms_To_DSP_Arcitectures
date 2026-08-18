// Sequence Detector (FSM)
// Detect the bit pattern "1101" in a serial input stream (overlapping allowed).
// This tests understanding of finite state machines and Mealy output logic.

`timescale 1ns / 1ps

// Test bench
module sequence_detector_tb();
    logic clk;
    logic rst_n;
    logic data_in;
    logic pattern_found;
    logic test_passed;
    logic [3:0] expected_detections;
    logic [3:0] actual_detections;

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // Instance of student's module
    sequence_detector dut(
        .clk(clk),
        .rst_n(rst_n),
        .data_in(data_in),
        .pattern_found(pattern_found)
    );

    // Task to send a sequence of bits
    task send_sequence;
    
        input logic [15:0] seq;
        input int length;
        begin
            for (int i = 0; i < length; i++) begin
                @(posedge clk);
                data_in = seq[i];
            end
        end
    endtask

    // Count pattern detections
    always @(posedge clk) begin
        if (!rst_n)
            actual_detections <= 0;
        else if (pattern_found)
            actual_detections <= actual_detections + 1;
    end

    initial begin
        test_passed = 1'b1;
        actual_detections = 0;
        expected_detections = 0;
        
        // Reset
        rst_n = 0;
        data_in = 0;
        #20;
        rst_n = 1;

        // Test Case 1: Simple pattern match "1011"
        expected_detections = 1;
        send_sequence(16'b1011_0000, 8);
        #20;
        if (actual_detections !== expected_detections) begin
            $display("Test 1 Failed: Expected %d pattern detection, got %d", 
                    expected_detections, actual_detections);
            test_passed = 1'b0;
        end

        // Test Case 2: Overlapping patterns "1011_1011"
        actual_detections = 0;
        expected_detections = 2;
        send_sequence(16'b1011_1011, 8);
        #20;
        if (actual_detections !== expected_detections) begin
            $display("Test 2 Failed: Expected %d pattern detections, got %d", 
                    expected_detections, actual_detections);
            test_passed = 1'b0;
        end

        // Test Case 3: Pattern with reset midway
        actual_detections = 0;
        expected_detections = 0;
        send_sequence(16'b1011, 2);
        rst_n = 0;
        #10;
        rst_n = 1;
        send_sequence(16'b11, 2);
        #20;
        if (actual_detections !== expected_detections) begin
            $display("Test 3 Failed: Reset not working properly");
            test_passed = 1'b0;
        end

        // Test Case 4: No pattern in sequence
        actual_detections = 0;
        expected_detections = 0;
        send_sequence(16'b1010_1000, 8);
        #20;
        if (actual_detections !== expected_detections) begin
            $display("Test 4 Failed: False detection in non-matching sequence");
            test_passed = 1'b0;
        end

        // Test Case 5: Multiple patterns with gaps
        actual_detections = 0;
        expected_detections = 2;
        send_sequence(16'b1011_0010_1011, 12);
        #20;
        if (actual_detections !== expected_detections) begin
            $display("Test 5 Failed: Expected %d pattern detections, got %d", 
                    expected_detections, actual_detections);
            test_passed = 1'b0;
        end

        if (test_passed)
            $display("PASS");
            
        $finish(0);
    end

    // Timeout watchdog
    initial begin
        #2000;
        $display("Test timed out!");
        $display("RESULT=0");
        $finish;
    end
endmodule