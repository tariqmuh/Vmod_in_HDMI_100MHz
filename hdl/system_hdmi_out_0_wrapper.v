//-----------------------------------------------------------------------------
// system_hdmi_out_0_wrapper.v
//-----------------------------------------------------------------------------

module system_hdmi_out_0_wrapper
  (
    PXL_CLK_X1,
    PXL_CLK_X2,
    PXL_CLK_X10,
    PXL_PLL_LOCKED,
    TMDS,
    TMDSB,
    S_AXI_ACLK,
    S_AXI_ARESETN,
    S_AXI_AWADDR,
    S_AXI_AWVALID,
    S_AXI_WDATA,
    S_AXI_WSTRB,
    S_AXI_WVALID,
    S_AXI_BREADY,
    S_AXI_ARADDR,
    S_AXI_ARVALID,
    S_AXI_RREADY,
    S_AXI_ARREADY,
    S_AXI_RDATA,
    S_AXI_RRESP,
    S_AXI_RVALID,
    S_AXI_WREADY,
    S_AXI_BRESP,
    S_AXI_BVALID,
    S_AXI_AWREADY,
    m_axi_aclk,
    m_axi_aresetn,
    md_error,
    m_axi_arready,
    m_axi_arvalid,
    m_axi_araddr,
    m_axi_arlen,
    m_axi_arsize,
    m_axi_arburst,
    m_axi_arprot,
    m_axi_arcache,
    m_axi_rready,
    m_axi_rvalid,
    m_axi_rdata,
    m_axi_rresp,
    m_axi_rlast,
    m_axi_awready,
    m_axi_awvalid,
    m_axi_awaddr,
    m_axi_awlen,
    m_axi_awsize,
    m_axi_awburst,
    m_axi_awprot,
    m_axi_awcache,
    m_axi_wready,
    m_axi_wvalid,
    m_axi_wdata,
    m_axi_wstrb,
    m_axi_wlast,
    m_axi_bready,
    m_axi_bvalid,
    m_axi_bresp
  );
  input PXL_CLK_X1;
  input PXL_CLK_X2;
  input PXL_CLK_X10;
  input PXL_PLL_LOCKED;
  output [3:0] TMDS;
  output [3:0] TMDSB;
  input S_AXI_ACLK;
  input S_AXI_ARESETN;
  input [31:0] S_AXI_AWADDR;
  input S_AXI_AWVALID;
  input [31:0] S_AXI_WDATA;
  input [3:0] S_AXI_WSTRB;
  input S_AXI_WVALID;
  input S_AXI_BREADY;
  input [31:0] S_AXI_ARADDR;
  input S_AXI_ARVALID;
  input S_AXI_RREADY;
  output S_AXI_ARREADY;
  output [31:0] S_AXI_RDATA;
  output [1:0] S_AXI_RRESP;
  output S_AXI_RVALID;
  output S_AXI_WREADY;
  output [1:0] S_AXI_BRESP;
  output S_AXI_BVALID;
  output S_AXI_AWREADY;
  input m_axi_aclk;
  input m_axi_aresetn;
  output md_error;
  input m_axi_arready;
  output m_axi_arvalid;
  output [31:0] m_axi_araddr;
  output [7:0] m_axi_arlen;
  output [2:0] m_axi_arsize;
  output [1:0] m_axi_arburst;
  output [2:0] m_axi_arprot;
  output [3:0] m_axi_arcache;
  output m_axi_rready;
  input m_axi_rvalid;
  input [31:0] m_axi_rdata;
  input [1:0] m_axi_rresp;
  input m_axi_rlast;
  input m_axi_awready;
  output m_axi_awvalid;
  output [31:0] m_axi_awaddr;
  output [7:0] m_axi_awlen;
  output [2:0] m_axi_awsize;
  output [1:0] m_axi_awburst;
  output [2:0] m_axi_awprot;
  output [3:0] m_axi_awcache;
  input m_axi_wready;
  output m_axi_wvalid;
  output [31:0] m_axi_wdata;
  output [3:0] m_axi_wstrb;
  output m_axi_wlast;
  output m_axi_bready;
  input m_axi_bvalid;
  input [1:0] m_axi_bresp;

  hdmi_out
    #(
      .HDMI_HRES ( 640 ),
      .HDMI_BYTES_PER_PIXEL ( 2 ),
      .C_S_AXI_DATA_WIDTH ( 32 ),
      .C_S_AXI_ADDR_WIDTH ( 32 ),
      .C_S_AXI_MIN_SIZE ( 32'h000002FF ),
      .C_USE_WSTRB ( 1 ),
      .C_DPHASE_TIMEOUT ( 8 ),
      .C_BASEADDR ( 32'h70e00000 ),
      .C_HIGHADDR ( 32'h70e0ffff ),
      .C_FAMILY ( "spartan6" ),
      .C_NUM_REG ( 3 ),
      .C_NUM_MEM ( 1 ),
      .C_SLV_AWIDTH ( 32 ),
      .C_SLV_DWIDTH ( 32 ),
      .C_M_AXI_ADDR_WIDTH ( 32 ),
      .C_M_AXI_DATA_WIDTH ( 32 ),
      .C_MAX_BURST_LEN ( 256 ),
      .C_NATIVE_DATA_WIDTH ( 32 ),
      .C_LENGTH_WIDTH ( 13 ),
      .C_ADDR_PIPE_DEPTH ( 1 )
    )
    hdmi_out_0 (
      .PXL_CLK_X1 ( PXL_CLK_X1 ),
      .PXL_CLK_X2 ( PXL_CLK_X2 ),
      .PXL_CLK_X10 ( PXL_CLK_X10 ),
      .PXL_PLL_LOCKED ( PXL_PLL_LOCKED ),
      .TMDS ( TMDS ),
      .TMDSB ( TMDSB ),
      .S_AXI_ACLK ( S_AXI_ACLK ),
      .S_AXI_ARESETN ( S_AXI_ARESETN ),
      .S_AXI_AWADDR ( S_AXI_AWADDR ),
      .S_AXI_AWVALID ( S_AXI_AWVALID ),
      .S_AXI_WDATA ( S_AXI_WDATA ),
      .S_AXI_WSTRB ( S_AXI_WSTRB ),
      .S_AXI_WVALID ( S_AXI_WVALID ),
      .S_AXI_BREADY ( S_AXI_BREADY ),
      .S_AXI_ARADDR ( S_AXI_ARADDR ),
      .S_AXI_ARVALID ( S_AXI_ARVALID ),
      .S_AXI_RREADY ( S_AXI_RREADY ),
      .S_AXI_ARREADY ( S_AXI_ARREADY ),
      .S_AXI_RDATA ( S_AXI_RDATA ),
      .S_AXI_RRESP ( S_AXI_RRESP ),
      .S_AXI_RVALID ( S_AXI_RVALID ),
      .S_AXI_WREADY ( S_AXI_WREADY ),
      .S_AXI_BRESP ( S_AXI_BRESP ),
      .S_AXI_BVALID ( S_AXI_BVALID ),
      .S_AXI_AWREADY ( S_AXI_AWREADY ),
      .m_axi_aclk ( m_axi_aclk ),
      .m_axi_aresetn ( m_axi_aresetn ),
      .md_error ( md_error ),
      .m_axi_arready ( m_axi_arready ),
      .m_axi_arvalid ( m_axi_arvalid ),
      .m_axi_araddr ( m_axi_araddr ),
      .m_axi_arlen ( m_axi_arlen ),
      .m_axi_arsize ( m_axi_arsize ),
      .m_axi_arburst ( m_axi_arburst ),
      .m_axi_arprot ( m_axi_arprot ),
      .m_axi_arcache ( m_axi_arcache ),
      .m_axi_rready ( m_axi_rready ),
      .m_axi_rvalid ( m_axi_rvalid ),
      .m_axi_rdata ( m_axi_rdata ),
      .m_axi_rresp ( m_axi_rresp ),
      .m_axi_rlast ( m_axi_rlast ),
      .m_axi_awready ( m_axi_awready ),
      .m_axi_awvalid ( m_axi_awvalid ),
      .m_axi_awaddr ( m_axi_awaddr ),
      .m_axi_awlen ( m_axi_awlen ),
      .m_axi_awsize ( m_axi_awsize ),
      .m_axi_awburst ( m_axi_awburst ),
      .m_axi_awprot ( m_axi_awprot ),
      .m_axi_awcache ( m_axi_awcache ),
      .m_axi_wready ( m_axi_wready ),
      .m_axi_wvalid ( m_axi_wvalid ),
      .m_axi_wdata ( m_axi_wdata ),
      .m_axi_wstrb ( m_axi_wstrb ),
      .m_axi_wlast ( m_axi_wlast ),
      .m_axi_bready ( m_axi_bready ),
      .m_axi_bvalid ( m_axi_bvalid ),
      .m_axi_bresp ( m_axi_bresp )
    );

endmodule

