
//`#start header` -- edit after this line, do not edit this line
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 02/13/2015 at 16:31
// Component: RowSync
module RowSync (
	output  clk_async,
	output [1:0] phase,
	output  sample,
	input   clk,
	input   href
);

//`#start body` -- edit after this line, do not edit this line
cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(0))
	async_clk(
		.clock_in	(clk),
		.enable		(1),
		.clock_out	(clk_async)
	);

reg href_;
reg [1:0] phase_;
assign phase=phase_;
always @(posedge clk_async) begin
	href_<=href;
	phase_<=href&&!href_?1:phase_+1;
end

assign sample=(phase==2'b11)&&href;

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
