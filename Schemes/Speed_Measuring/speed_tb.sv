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

    // Параметры
    localparam CLK_PERIOD = 1.0 / 12_000_000.0 * 1_000_000_000; // Период тактового сигнала в нс

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

    // Генератор тактового сигнала
    initial begin
        clk = 0;
        forever #(CLK_PERIOD / 2) clk = ~clk;
    end

    initial begin
        // Инициализация
        rst = 1;
        sensor_a = 0;
        sensor_b = 0;
        #100;
        rst = 0;
        #100;
        
        // Стартовый сигнал от первого датчика
        sensor_a = 1;
        #CLK_PERIOD;
        sensor_a = 0;

        // Ожидание (3/320) секунды
        
        // Пытался сделать через формулу #(3 * 1_000_000_000 / 320),
        // однако не получилось: sensor_b переходил в 1 сразу
        // посде перехода sensor_a в 0
        #9375000;

        // Сигнал от второго датчика
        sensor_b = 1;
        #CLK_PERIOD;
        sensor_b = 0;

        // Задержка для расчета скорости
        #10000;

        // Проверка значений сегментов
        $display("seg1: %b (expected: 7'b1011011 for digit 2)", seg1);
        $display("seg2: %b (expected: 7'b1001111 for digit 3)", seg2);
        $display("seg3: %b (expected: 7'b0000000 for blank)", seg3);
        $display("seg4: %b (expected: 7'b0000000 for blank)", seg4);

        // Завершение симуляции
        $finish;
    end

endmodule

