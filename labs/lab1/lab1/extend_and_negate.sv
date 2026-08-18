`timescale 1ns / 1ps
module extend_and_negate(
    input  logic [3:0] in,    
    output logic [7:0] out    
);
    // Your code goes here
    wire [7:0] extended;

    
    assign extended = {{4{in[3]}}, in};

    assign out = -extended;

endmodule

