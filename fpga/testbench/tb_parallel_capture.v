`timescale 1ns/1ps

module tb_parallel_capture;

    reg         clk;
    reg         rst_n;
    reg         cs_n;
    reg  [3:0]  data_in;
    wire        irq;

    integer errors;

    // Instantiate the design
    parallel_capture dut (
        .clk     (clk),
        .rst_n   (rst_n),
        .cs_n    (cs_n),
        .data_in (data_in),
        .irq     (irq)
    );

    // Clock generation: 50 MHz
    initial clk = 1'b0;
    always #10 clk = ~clk;   // 20 ns period

    // Send one 4-bit sample
    task send_sample;
        input [3:0] sample;
        begin
            data_in = sample;
            @(posedge clk);
            #1; // allow nonblocking assignments to update
        end
    endtask

    // Simple check helper
    task check_irq;
        input expected;
        begin
            if (irq !== expected) begin
                $display(
                    "ERROR at %0t ns: irq = %b, expected %b",
                    $time,
                    irq,
                    expected
                );
                errors = errors + 1;
            end
        end
    endtask

    initial begin
        // Generate waveform for GTKWave
        $dumpfile("parallel_capture.vcd");
        $dumpvars(0, tb_parallel_capture);

        errors  = 0;
        rst_n   = 0;
        cs_n    = 1;
        data_in = 4'h0;

        // ---------------- Reset test ----------------
        #50;
        rst_n = 1;
        #20;

        check_irq(1'b0);

        // ---------------- First capture session ----------------
        cs_n = 0;

        // IRQ should remain low through the first 7 samples
        send_sample(4'h1);
        check_irq(1'b0);

        send_sample(4'h2);
        check_irq(1'b0);

        send_sample(4'h3);
        check_irq(1'b0);

        send_sample(4'h4);
        check_irq(1'b0);

        send_sample(4'h5);
        check_irq(1'b0);

        send_sample(4'h6);
        check_irq(1'b0);

        send_sample(4'h7);
        check_irq(1'b0);

        // IRQ should assert when the 8th sample is captured
        send_sample(4'h8);
        check_irq(1'b1);

        // Continue capturing several more samples
        send_sample(4'h9);
        check_irq(1'b1);

        send_sample(4'hA);
        send_sample(4'hB);
        send_sample(4'hC);

        // End capture session
        cs_n = 1;
        @(posedge clk);
        #1;

        // IRQ and internal capture state should reset
        check_irq(1'b0);

        if (dut.count !== 5'd0) begin
            $display(
                "ERROR at %0t ns: count = %0d after CS release, expected 0",
                $time,
                dut.count
            );
            errors = errors + 1;
        end

        if (dut.wr_ptr !== 4'd0) begin
            $display(
                "ERROR at %0t ns: wr_ptr = %0d after CS release, expected 0",
                $time,
                dut.wr_ptr
            );
            errors = errors + 1;
        end

        // ---------------- Second capture session ----------------
        // Verify that a new session starts from a clean state
        cs_n = 0;

        send_sample(4'h1);
        check_irq(1'b0);

        send_sample(4'h2);
        check_irq(1'b0);

        send_sample(4'h3);
        check_irq(1'b0);

        send_sample(4'h4);
        check_irq(1'b0);

        send_sample(4'h5);
        check_irq(1'b0);

        send_sample(4'h6);
        check_irq(1'b0);

        send_sample(4'h7);
        check_irq(1'b0);

        send_sample(4'h8);
        check_irq(1'b1);

        // End second capture session
        cs_n = 1;
        @(posedge clk);
        #1;

        check_irq(1'b0);

        // ---------------- Final result ----------------
        if (errors == 0)
            $display("PASS: All parallel capture tests passed.");
        else
            $display("FAIL: %0d test(s) failed.", errors);

        #20;
        $finish;
    end

endmodule
