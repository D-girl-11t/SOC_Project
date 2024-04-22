module flip(clk, en, d, q);
wire cg0;
  wire 0;
  input clk;
  wire clk;
  input d;
  wire d;
  input en;
  wire en;
  output q;
  wire q;
sky130_fd_sc_hd__inv_1 0 (
.A(en),
.Y(cg0),
);
sky_130_fd_sc_hd_and21 0 (
.A(clk),
.B(cg0),
.X(0)
);
sky130_fd_sc_hd_dfxtp_1 \q$_DFFE_PP  (
.CLK(0),
.D(q),
.Q(q)
);
endmodule
