module flip(clk, en, d, q);
  wire 0;
  input clk;
  wire clk;
  input d;
  wire d;
  input en;
  wire en;
  output q;
  wire q;
  sky130_fd_sc_hd_mux2_4 _1 (
    .A0(q),
    .A1(d),
    .S(en),
    .X(0)
  );
  sky130_fd_sc_hd_dfxtp_1 \q$_DFFE_PP  (
    .CLK(clk),
    .D(0),
    .Q(q)
  );
endmodule
