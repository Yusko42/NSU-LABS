`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 29.05.2024 12:47:53
// Design Name: 
// Module Name: speed_tb
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


module speed_tb;

    // ���������
    localparam CLK_PERIOD = 1.0 / 12_000_000.0 * 1_000_000_000; // ������ ��������� ������� � ��

    logic clk;
    logic rst;
    logic sensor_a;
    logic sensor_b;

    logic [6:0] seg1;
    logic [6:0] seg2;
    logic [6:0] seg3;
    logic [6:0] seg4;

    speed_measure dut (
        .clk(clk),
        .rst(rst),
        .sensor_a(sensor_a),
        .sensor_b(sensor_b),
        .seg1(seg1),
        .seg2(seg2),
        .seg3(seg3),
        .seg4(seg4)
    );

    // ��������� ��������� �������
    initial begin
        clk = 0;
        forever #(CLK_PERIOD / 2) clk = ~clk;
    end

    initial begin
        // �������������
        rst = 1;
        sensor_a = 0;
        sensor_b = 0;
        #100;
        rst = 0;
        #100;
        
        // ��������� ������ �� ������� �������
        sensor_a = 1;
        #CLK_PERIOD;
        sensor_a = 0;

        // �������� (3/320) �������
        
        // ������� ������� ����� ������� #(3 * 1_000_000_000 / 320),
        // ������ �� ����������: sensor_b ��������� � 1 �����
        // ����� �������� sensor_a � 0
        #9375000;

        // ������ �� ������� �������
        sensor_b = 1;
        #CLK_PERIOD;
        sensor_b = 0;

        // �������� ��� ������� ��������
        #10000;

        // �������� �������� ���������
        $display("seg1: %b (expected: 7'b1011011 for digit 2)", seg1);
        $display("seg2: %b (expected: 7'b1001111 for digit 3)", seg2);
        $display("seg3: %b (expected: 7'b0000000 for blank)", seg3);
        $display("seg4: %b (expected: 7'b0000000 for blank)", seg4);

        // ���������� ���������
        $finish;
    end

endmodule

