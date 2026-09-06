`timescale 1ns/1ps

module tb_parallel_capture;

    reg         clk;
    reg         rst_n;
    reg         cs_n;
    reg  [3:0]  data_in;
    wire        irq;

    // Instantiate the design
    parallel_capture dut (
        .clk     (clk),
        .rst_n   (rst_n),
        .cs_n    (cs_n),
        .data_in (data_in),
        .irq     (irq)
    );

    // Clock generation (50 MHz)
    initial clk = 0;
    always #10 clk = ~clk;   // 20 ns period → 50 MHz

    // Test sequence
    initial begin
        // Dump waves for GTKWave
        $dumpfile("parallel_capture.vcd");
        $dumpvars(0, tb_parallel_capture);

        // Initialize
        rst_n   = 0;
        cs_n    = 1;
        data_in = 4'h0;

        // Reset
        #50;
        rst_n = 1;
        #20;

        // Start capturing data
        cs_n = 0;

        // Send 12 different data values
        data_in = 4'h1; #20;
        data_in = 4'h2; #20;
        data_in = 4'h3; #20;
        data_in = 4'h4; #20;
        data_in = 4'h5; #20;
        data_in = 4'h6; #20;
        data_in = 4'h7; #20;
        data_in = 4'h8; #20;
        data_in = 4'h9; #20;
        data_in = 4'hA; #20;
        data_in = 4'hB; #20;
        data_in = 4'hC; #20;

        // Release chip select
        cs_n = 1;
        #100;

        $display("Simulation finished");
        $finish;
    end

endmodule
