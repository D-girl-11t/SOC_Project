module flip(clk, en, d, q);
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
  sky130_fd_sc_hd_inv_1 _2 (
    .A(clk),
    .Y(0)
  );
  sky130_fd_sc_hd_mux2_4 _3 (
    .A0(q),
    .A1(d),
    .S(en),
    .X(1)
  );
  sky130_fd_sc_hd_dfxtp_1 \q$_DFFE_NP  (
    .CLK(0),
    .D(1),
    .Q(q)
  );
endmodule