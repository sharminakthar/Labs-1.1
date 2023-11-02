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
logic [2:0] func;
logic ROMO, RAMO, RAMW, SWBEN, LEDLTCH;

controller asm (.*);

initial
  begin
  clk = 0;
  func = 5;
  #10ns clk = 1;
  end
  
endmodule