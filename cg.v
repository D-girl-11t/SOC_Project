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
sky_130_fd_sc_hd_and21 0 (
.A(0),
.B(en),
.X(1)
);
sky130_fd_sc_hd_dfxtp_1 \q$_DFFE_NP  (
.CLK(1),
.D(d),
.Q(q)
  );
endmodule
