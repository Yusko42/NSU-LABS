`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.05.2024 21:29:29
// Design Name: 
// Module Name: speed_measure
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module speed_measure(
    input logic clk, // 12 MHz clock
    input logic rst, // reset - for initialization
    input logic sensor_a,
    input logic sensor_b,
    output logic [6:0] seg1,
    output logic [6:0] seg2,
    output logic [6:0] seg3,
    output logic [6:0] seg4
    );
    
    logic [23:0] count;
    logic [23:0] time_counted;
    logic sensor_a_last = 0;
    logic sensor_b_last = 0;
    logic in_process = 0;
    
    // Time counter
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin // Counter init
            count <= 24'd0;
            sensor_a_last <= 0;
            sensor_b_last <= 0;
            in_process <= 0;
        end else begin
            sensor_a_last <= sensor_a;
            sensor_b_last <= sensor_b;
            if (sensor_a && !sensor_a_last) begin
                in_process <= 1;
                count <= 24'd0;
            end else if (sensor_b && !sensor_b_last) begin
                in_process <= 0;
                time_counted <= count;
            end
            else if (in_process) begin
                count <= count + 1;
            end
        end
    end
    
    // Speed calculation (12 MHz * 30 cm / time)
    logic [5:0] speed_calc = (360_000_000 / time_counted);
    
    // Display output
    SevenSegmentDisplay display (
        .clk(clk),
        .reset(rst),
        .value(speed_calc),
        .seg1(seg1),
        .seg2(seg2),
        .seg3(seg3),
        .seg4(seg4)
    );
    
endmodule

module SevenSegmentDisplay(
    input logic clk,
    input logic reset,
    input logic [5:0] value,
    output logic [6:0] seg1,
    output logic [6:0] seg2,
    output logic [6:0] seg3,
    output logic [6:0] seg4
);
    
    logic [3:0] digit[3:0]; // Array to hold each digit

    // Split the value into individual digits
    always_comb begin
        digit[0] = value % 10;
        digit[1] = (value / 10) % 10;
        digit[2] = 0;
        digit[3] = 0;
    end

    // Segment decoding for each digit
    always_comb begin
        // Digit 0
        case (digit[0])
            4'h0: seg1 = 7'b0111111;
            4'h1: seg1 = 7'b0000110;
            4'h2: seg1 = 7'b1011011;
            4'h3: seg1 = 7'b1001111;
            4'h4: seg1 = 7'b1100110;
            4'h5: seg1 = 7'b1101101;
            4'h6: seg1 = 7'b1111101;
            4'h7: seg1 = 7'b0000111;
            4'h8: seg1 = 7'b1111111;
            4'h9: seg1 = 7'b1101111;
            default: seg1 = 7'b0000000; // Blank
        endcase

        // Digit 1
        case (digit[1])
            4'h0: seg2 = 7'b0111111;
            4'h1: seg2 = 7'b0000110;
            4'h2: seg2 = 7'b1011011;
            4'h3: seg2 = 7'b1001111;
            4'h4: seg2 = 7'b1100110;
            4'h5: seg2 = 7'b1101101;
            4'h6: seg2 = 7'b1111101;
            4'h7: seg2 = 7'b0000111;
            4'h8: seg2 = 7'b1111111;
            4'h9: seg2 = 7'b1101111;
            default: seg2 = 7'b0000000; // Blank
        endcase

        // Digits 2 and 3 are always blank here
        seg3 = 7'b0000000;
        seg4 = 7'b0000000;
    end
    
endmodule
