module flip(clk, en, d, q, d1, q1);
  wire 0;
   wire 1;
  input clk;
  wire clk;
  input d;
  wire d;
  input en;
  wire en;
  output q;
  wire q;
  wire d1;
  wire q1;
  sky130_fd_sc_hd_mux2_4 _1 (
    .A0(q),
    .A1(d),
    .S(en),
    .X(0)
  );
  sky130_fd_sc_hd_mux2_4 _2 (
    .A0(q1),
    .A1(d1),
    .S(en),
    .X(0)
  );
  sky130_fd_sc_hd_dfxtp_1 \q$_DFFE_PP  (
    .CLK(clk),
    .D(0),
    .Q(q)
  );
endmodule