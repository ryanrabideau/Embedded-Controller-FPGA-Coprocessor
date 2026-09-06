module parallel_capture (
    input  wire        clk,
    input  wire        rst_n,
    input  wire        cs_n,
    input  wire [3:0]  data_in,
    output reg         irq
);

    // 16-deep × 4-bit buffer
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
                // Capture data
                buffer[wr_ptr] <= data_in;
                wr_ptr <= wr_ptr + 1'b1;

                if (count < 5'd16)
                    count <= count + 1'b1;

                // Raise interrupt once we have at least 8 samples
                if (count >= 5'd7)      // will become 8 after this write
                    irq <= 1'b1;
            end
            else begin
                // When CS is released, clear interrupt and optionally reset count
                irq   <= 1'b0;
                // Uncomment the next line if you want the buffer to clear when CS goes high
                // count <= 5'd0;
            end
        end
    end

endmodule
