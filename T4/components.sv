/////////////////////////////////////////////////////////////////////
// Design unit: 
//            :
// File name  : components.sv
//            :
// Description: Components for PlayBus emulator
//            : Simplified version. Smaller address space. Positive logic.
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
// Revision   : Version 1.0 23/08/17
//            : 
/////////////////////////////////////////////////////////////////////



module contention (output logic contend, Z, input logic RAMO, ROMO, SWBEN);

always_comb
  begin
  Z = ~(RAMO | ROMO | SWBEN);
  contend = (RAMO & ROMO) | (RAMO & SWBEN) | (SWBEN & ROMO);
  end
  
endmodule

//emulates EPROM with data
module eprom (output wire [3:0] data, input logic [2:0] address, input logic OE, CS);

logic [3:0] prom [0:7] =  '{4'b0000, 
                            4'b0001, 
                            4'b0011, 
                            4'b0010, 
                            4'b0110,
                            4'b0111, 
                            4'b0101,
                            4'b0100};
                          
assign data = (OE & CS) ? prom[address] : 'Z;
  
endmodule

//emulates SRAM
module ram (inout wire [3:0] data, 
            input logic [2:0] address, 
            input logic CS, WE, OE, clk);

  logic [3:0] mem [0:7];

  assign data = (CS & OE) ? mem[address] : 'Z;

  always_ff @(posedge clk)
    if (CS & WE)
      mem[address] <= data;

endmodule

module sevenseg(output logic [6:0] seg, 
                input logic [3:0] value, input logic Z, contend);

//extended to show hex + contention and float

always_comb
  unique casez ({Z,contend,value})
    6'b000000 : seg = 7'b1000000;
    6'b000001 : seg = 7'b1111001;
    6'b000010 : seg = 7'b0100100;
    6'b000011 : seg = 7'b0110000;
    6'b000100 : seg = 7'b0011001;
    6'b000101 : seg = 7'b0010010;
    6'b000110 : seg = 7'b0000010;
    6'b000111 : seg = 7'b1111000;
    6'b001000 : seg = 7'b0000000;
    6'b001001 : seg = 7'b0010000;
    6'b001010 : seg = 7'b0001000;
    6'b001011 : seg = 7'b0000011;
    6'b001100 : seg = 7'b1000110;
    6'b001101 : seg = 7'b0100001;
    6'b001110 : seg = 7'b0000110;
    6'b001111 : seg = 7'b0001110;
    6'b01???? : seg = 7'b1000001; //U for undefined = contention
    6'b1????? : seg = 7'b0001001; //H for high impedance
    default : seg = 7'b1111111; 
  endcase
endmodule

//
module register #(parameter N = 4) (output logic [N-1:0] data_out, input logic [N-1:0] data_in, 
                               input logic OE, clk);

always_ff @(posedge clk)
  if (OE)
    data_out <= data_in;
    
endmodule

//
module buffer #(parameter N = 4) (output wire [N-1:0] data, input logic [N-1:0] data_in, 
                                input logic OE, CS);

assign data = (OE & CS) ? data_in : 'Z;
  
endmodule