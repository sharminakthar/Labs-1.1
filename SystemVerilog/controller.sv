/////////////////////////////////////////////////////////////////////
// Design unit: controller
//            :
// File name  : controller.sv
//            :
// Description: Controller for PlayBus level 1 emulator
//            :
// Limitations: None
//            :
// System     : SystemVerilog IEEE 1800-2005
//            :
// Author     : Mark Zwolinski
//            : School of Electronics and Computer Science
//            : University of Southampton
//            : Southampton SO17 1BJ, UK
//            : mz@ecs.soton.ac.uk
//
// Revision   : Version 1.0 24/08/17
//            :
/////////////////////////////////////////////////////////////////////

module controller (input logic clk, input logic [2:0] func,
                   output logic ROMO, RAMO, RAMW, SWBEN, LEDLTCH);

enum {start, xfer} present_state, next_state;

always_ff @(posedge clk)
  present_state <= next_state;

always_comb
  begin
  ROMO = '0;
  RAMO = '0;
  RAMW = '0;
  SWBEN = '0;
  LEDLTCH = '0;
  next_state = present_state;
  case (present_state)
    start: begin
		if ((func == 0) || (func == 4))
			ROMO = 1;
		if ((func == 1) || (func == 7))
			RAMO = 1;
	    if ((func == 2) || (func == 3) || (func == 5))
			begin
			SWBEN = '1;
			end
		if ((func == 3) || (func == 4))
			begin
			RAMW = 1;
			next_state = xfer;
			end
	    if ((func == 5) || (func == 6) || (func == 7))
			begin
			LEDLTCH = '1;
			next_state = xfer;
			end;
	   end
    xfer : next_state = start;
    endcase
  end

endmodule