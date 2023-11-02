/////////////////////////////////////////////////////////////////////
// Design unit: test_playbus0
//            :
// File name  : test_playbus0.sv
//            :
// Description: PlayBus level 0 testbench
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

module test_playbus1;

   logic [6:0] disp0, disp1;
   logic [3:0] sw0;
   logic       RAMO, ROMO, SWBEN, RAMW, LEDLTCH, n_clk;

   full_playbus1 p1 (.*);

   initial
     begin
        RAMO = 0;
        ROMO = 0;
        SWBEN = 0;
        RAMW = 0;
        LEDLTCH = 0;
        sw0 = 4'b0000;
        #10ns sw0 = 4'b1010;
        SWBEN = 1;
        LEDLTCH = 1;
        #10ns n_clk = 0;
     end

   initial
     begin
        n_clk = 1;
        forever #10ns n_clk = ~n_clk;
     end
endmodule
