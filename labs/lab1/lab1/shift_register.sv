`timescale 1ns / 1ps

module shift_register(
    input  logic clk,
    input  logic rst_n,
    input  logic load,      // Load parallel input 
    input  logic shift,     // Shift right
  input  logic [7:0] d_in,  // parallel input
    input  logic serial_in, // serial input
    output logic [7:0] q    // parallel output 
);

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin      
      q <= 8'b0;
    end 
    
    else if (load) begin
      q <= d_in;
    end 
    
    else if (shift) begin
      q <= {serial_in, q[7:1]};
    end

  end

endmodule