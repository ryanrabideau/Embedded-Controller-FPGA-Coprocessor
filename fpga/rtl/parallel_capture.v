module parallel_capture (
    input  wire        clk,
    input  wire        rst_n,
    input  wire        cs_n,
    input  wire [3:0]  data_in,
    output reg         irq
);

    // 16-deep x 4-bit buffer
    reg [3:0] buffer [0:15];
    reg [3:0] wr_ptr;
    reg [4:0] count;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wr_ptr <= 4'd0;
            count  <= 5'd0;
            irq    <= 1'b0;
        end
        else begin
            if (!cs_n) begin
                // Capture one 4-bit sample on each rising clock edge
                buffer[wr_ptr] <= data_in;
                wr_ptr <= wr_ptr + 1'b1;

                // Saturate count at the 16-sample buffer depth
                if (count < 5'd16)
                    count <= count + 1'b1;

                // Assert IRQ when the 8th sample is captured
                if (count >= 5'd7)
                    irq <= 1'b1;
            end
            else begin
                // End of capture session: clear state for next transaction
                wr_ptr <= 4'd0;
                count  <= 5'd0;
                irq    <= 1'b0;
            end
        end
    end

endmodule
