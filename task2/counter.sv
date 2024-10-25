module counter #(
    parameter WIDTH = 8
)(
    //interface signals
    input logic     clk,            //clock
    input logic     rst,            //reset
    input logic     en,             //counter enable
    output logic [WIDTH-1:0] count  //count output
);

always_ff @ (posedge clk, posedge rst)
    if (en) count <= count + {{WIDTH-1{1'b0}}, {1'b1}}; //edit logic for enable, if enable is high we add 1 bit, and if low then subtract 1 bit for each clock cycle
    else count <= count - {{WIDTH-1{1'b0}}, {1'b1}};

endmodule
