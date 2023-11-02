/////////////////////////////////////////////////////////////////////
// Design unit: test_controller
//            :
// File name  : test_controller.sv
//            :
// Description: PlayBus level 1 controller testbench
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


module test_controller;

logic clk;
logic [2:0] address, func;
logic [3:0] switches;
logic [6:0] disp0, disp1, disp2, disp3;

full_playbus1 p1 (.disp0(disp0), .disp1(disp1), .disp2(disp2), .disp3(disp3),
				  .sw0(switches), .sw1(address), .sw2(func), .clk(clk));
// controller asm (.*);

initial
  begin
	clk = 0;
	address = 0;
	func = 5;
	disp0 = 0;
	disp1 = 0;
	disp2 = 0;
	disp3 = 0;
	
	switches = 4'b1010;
	func = 0;
	#10ns clk = 1;
	#10ns clk = 0; // copy data from switch to ram at address
	func = 3;
	address = 2;
	#10ns clk = 1;
	#10ns clk = 1;
	#10ns clk = 0;
	#10ns clk = 0; // read data from ram to bus at address
	func = 1;
	#10ns clk = 1;
	#10ns clk = 0; // read data from switch to bus
	func = 2;
	#10ns clk = 1;
	#10ns clk = 0; // copy data from switch to leds
	func = 5;
	#10ns clk = 1;
	#10ns clk = 1;
	#10ns clk = 0;
	#10ns clk = 0; // copy data from eprom into ram at address
	func = 4;
	#10ns clk = 1;
	#10ns clk = 1;
	#10ns clk = 0;
	#10ns clk = 0; // copy data from EPROM at address into LEDs at address
	func = 6;
	#10ns clk = 1;
	#10ns clk = 1;
	#10ns clk = 0;
	#10ns clk = 0; // Copy data from RAM at address into LEDs
	func = 7;
	#10ns clk = 1;
	#10ns clk = 1;
	#10ns clk = 0;
  end
// initial
 // begin
	// clk = 0;
	// forever #10ns clk = ~clk;
 // end
endmodule