// Sign Extension and Negation
// Given a 4-bit signed input, sign-extend it to 8 bits and negate (2's complement).
// This tests understanding of signed number representation.

`timescale 1ns / 1ps

module extend_and_negate_tb();
    logic [3:0] in;
    logic [7:0] out;
    logic test_passed;

    extend_and_negate dut(
        .in(in),
        .out(out)
    );

    initial begin
        test_passed = 1'b1;
        
        // Test Case 1: +5 should become -5
        in = 4'b0101;  // +5
        #10;
        if (signed'(out) !== -8'd5) begin
            $display("Test failed for input +5 (0101): Expected -5 (11111011), Got %b", out);
            test_passed = 1'b0;
        end

        // Test Case 2: -5 should become +5
        in = 4'b1011;  // -5
        #10;
        if (signed'(out) !== 8'd5) begin
            $display("Test failed for input -5 (1011): Expected +5 (00000101), Got %b", out);
            test_passed = 1'b0;
        end

        // Test Case 3: Zero should map to zero
        in = 4'b0000;  // 0
        #10;
        if (out !== 8'b00000000) begin
            $display("Test failed for input 0 (0000): Expected 0 (00000000), Got %b", out);
            test_passed = 1'b0;
        end

        // Test Case 4: Most negative 4-bit number (-8) should become +8
        in = 4'b1000;  // -8
        #10;
        if (signed'(out) !== 8'd8) begin
            $display("Test failed for input -8 (1000): Expected +8 (00001000), Got %b", out);
            test_passed = 1'b0;
        end

        // Test Case 5: Most positive 4-bit number (+7) should become -7
        in = 4'b0111;  // +7
        #10;
        if (signed'(out) !== -8'd7) begin
            $display("Test failed for input +7 (0111): Expected -7 (11111001), Got %b", out);
            test_passed = 1'b0;
        end

        // Test Case 6: -1 should become +1
        in = 4'b1111;  // -1
        #10;
        if (signed'(out) !== 8'd1) begin
            $display("Test failed for input -1 (1111): Expected +1 (00000001), Got %b", out);
            test_passed = 1'b0;
        end

        if (test_passed)
            $display("PASS");
            
        // $display("RESULT=%b", test_passed);
        $finish(0);
    end
endmodule
