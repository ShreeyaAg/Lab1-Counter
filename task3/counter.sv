module counter #(
  parameter WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock 
  input  logic             rst,      // reset 
  input  logic             ld,       // load counter from data
  input  logic [WIDTH-1:0] v,        // value to preload
  //pre loaded values and a load counter which will load the vdcvalue 
  output logic [WIDTH-1:0] count     // count output
);

always_ff @ (posedge clk)
  if (rst) count <= {WIDTH{1'b0}};
  else     count <= ld ? count + {{WIDTH-1{1'b0}},1'b1} : count;
  //if load is high load preloaded value or if the counter will continue going up 
  //muliplexer 

endmodule
