/////////////////////////////////////////////////////////////////////
// Design unit: 
//            :
// File name  : playbus0.sv
//            :
// Description: PlayBus level 0 emulator
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


// Version 0 uses 5 switches to control sources and sinks
// disp0 shows output value
// disp1 shows state of bus
// 

module playbus0 (output logic [6:0] disp0, disp1,  
                input logic [3:0] sw0, input logic RAMO, ROMO, SWBEN, RAMW, LEDLTCH, 
                input logic n_clk);
                
wire [3:0] data; // this is the main system bus
logic [3:0] ledout;
logic [2:0] address;
logic contend, Z, clk;

assign clk = ~n_clk;
assign address = 3'b101;

contention c0 (.*);
eprom e0 (.data(data), .address(address), .OE(ROMO), .CS(~contend));
ram r0 (.data(data), .address(address), .OE(RAMO), .CS(~contend), .WE(RAMW), .clk(clk));
register #(4) l2 (.data_out(ledout), .data_in(data), .OE(LEDLTCH), .clk(clk));
buffer #(4) b0 (.data(data), .data_in(sw0), .OE(SWBEN), .CS(~contend));
sevenseg s0 (.seg(disp0), .value(ledout), .Z(1'b0), .contend(1'b0));
sevenseg s1 (.seg(disp1), .value (data), .Z(Z), .contend(contend));

endmodule