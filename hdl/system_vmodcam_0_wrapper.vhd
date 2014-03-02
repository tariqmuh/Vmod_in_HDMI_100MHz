-------------------------------------------------------------------------------
-- system_vmodcam_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library vmodcam_v1_00_a;
use vmodcam_v1_00_a.all;

entity system_vmodcam_0_wrapper is
  port (
    SW_I : in std_logic_vector(7 downto 0);
    LED_O : out std_logic_vector(7 downto 0);
    RESET_I : in std_logic;
    CamClk : in std_logic;
    CamClk_180 : in std_logic;
    CAMA_SDA : inout std_logic;
    CAMA_SCL : inout std_logic;
    CAMA_D_I : inout std_logic_vector(7 downto 0);
    CAMA_PCLK_I : inout std_logic;
    CAMA_MCLK_O : out std_logic;
    CAMA_LV_I : inout std_logic;
    CAMA_FV_I : inout std_logic;
    CAMA_RST_O : out std_logic;
    CAMA_PWDN_O : out std_logic;
    CAMX_VDDEN_O : out std_logic;
    CAMB_SDA : inout std_logic;
    CAMB_SCL : inout std_logic;
    CAMB_D_I : inout std_logic_vector(7 downto 0);
    CAMB_PCLK_I : inout std_logic;
    CAMB_MCLK_O : out std_logic;
    CAMB_LV_I : inout std_logic;
    CAMB_FV_I : inout std_logic;
    CAMB_RST_O : out std_logic;
    CAMB_PWDN_O : out std_logic;
    S_AXI_ACLK : in std_logic;
    S_AXI_ARESETN : in std_logic;
    S_AXI_AWADDR : in std_logic_vector(31 downto 0);
    S_AXI_AWVALID : in std_logic;
    S_AXI_WDATA : in std_logic_vector(31 downto 0);
    S_AXI_WSTRB : in std_logic_vector(3 downto 0);
    S_AXI_WVALID : in std_logic;
    S_AXI_BREADY : in std_logic;
    S_AXI_ARADDR : in std_logic_vector(31 downto 0);
    S_AXI_ARVALID : in std_logic;
    S_AXI_RREADY : in std_logic;
    S_AXI_ARREADY : out std_logic;
    S_AXI_RDATA : out std_logic_vector(31 downto 0);
    S_AXI_RRESP : out std_logic_vector(1 downto 0);
    S_AXI_RVALID : out std_logic;
    S_AXI_WREADY : out std_logic;
    S_AXI_BRESP : out std_logic_vector(1 downto 0);
    S_AXI_BVALID : out std_logic;
    S_AXI_AWREADY : out std_logic;
    m_axi_aclk : in std_logic;
    m_axi_aresetn : in std_logic;
    md_error : out std_logic;
    m_axi_arready : in std_logic;
    m_axi_arvalid : out std_logic;
    m_axi_araddr : out std_logic_vector(31 downto 0);
    m_axi_arlen : out std_logic_vector(7 downto 0);
    m_axi_arsize : out std_logic_vector(2 downto 0);
    m_axi_arburst : out std_logic_vector(1 downto 0);
    m_axi_arprot : out std_logic_vector(2 downto 0);
    m_axi_arcache : out std_logic_vector(3 downto 0);
    m_axi_rready : out std_logic;
    m_axi_rvalid : in std_logic;
    m_axi_rdata : in std_logic_vector(31 downto 0);
    m_axi_rresp : in std_logic_vector(1 downto 0);
    m_axi_rlast : in std_logic;
    m_axi_awready : in std_logic;
    m_axi_awvalid : out std_logic;
    m_axi_awaddr : out std_logic_vector(31 downto 0);
    m_axi_awlen : out std_logic_vector(7 downto 0);
    m_axi_awsize : out std_logic_vector(2 downto 0);
    m_axi_awburst : out std_logic_vector(1 downto 0);
    m_axi_awprot : out std_logic_vector(2 downto 0);
    m_axi_awcache : out std_logic_vector(3 downto 0);
    m_axi_wready : in std_logic;
    m_axi_wvalid : out std_logic;
    m_axi_wdata : out std_logic_vector(31 downto 0);
    m_axi_wstrb : out std_logic_vector(3 downto 0);
    m_axi_wlast : out std_logic;
    m_axi_bready : out std_logic;
    m_axi_bvalid : in std_logic;
    m_axi_bresp : in std_logic_vector(1 downto 0)
  );
end system_vmodcam_0_wrapper;

architecture STRUCTURE of system_vmodcam_0_wrapper is

  component vmodcam is
    generic (
      DEBUG_EN : INTEGER;
      COLORDEPTH : INTEGER;
      C_S_AXI_DATA_WIDTH : INTEGER;
      C_S_AXI_ADDR_WIDTH : INTEGER;
      C_S_AXI_MIN_SIZE : std_logic_vector;
      C_USE_WSTRB : INTEGER;
      C_DPHASE_TIMEOUT : INTEGER;
      C_BASEADDR : std_logic_vector;
      C_HIGHADDR : std_logic_vector;
      C_FAMILY : STRING;
      C_NUM_REG : INTEGER;
      C_NUM_MEM : INTEGER;
      C_SLV_AWIDTH : INTEGER;
      C_SLV_DWIDTH : INTEGER;
      C_M_AXI_ADDR_WIDTH : INTEGER;
      C_M_AXI_DATA_WIDTH : INTEGER;
      C_MAX_BURST_LEN : INTEGER;
      C_NATIVE_DATA_WIDTH : INTEGER;
      C_LENGTH_WIDTH : INTEGER;
      C_ADDR_PIPE_DEPTH : INTEGER
    );
    port (
      SW_I : in std_logic_vector(7 downto 0);
      LED_O : out std_logic_vector(7 downto 0);
      RESET_I : in std_logic;
      CamClk : in std_logic;
      CamClk_180 : in std_logic;
      CAMA_SDA : inout std_logic;
      CAMA_SCL : inout std_logic;
      CAMA_D_I : inout std_logic_vector(7 downto 0);
      CAMA_PCLK_I : inout std_logic;
      CAMA_MCLK_O : out std_logic;
      CAMA_LV_I : inout std_logic;
      CAMA_FV_I : inout std_logic;
      CAMA_RST_O : out std_logic;
      CAMA_PWDN_O : out std_logic;
      CAMX_VDDEN_O : out std_logic;
      CAMB_SDA : inout std_logic;
      CAMB_SCL : inout std_logic;
      CAMB_D_I : inout std_logic_vector(7 downto 0);
      CAMB_PCLK_I : inout std_logic;
      CAMB_MCLK_O : out std_logic;
      CAMB_LV_I : inout std_logic;
      CAMB_FV_I : inout std_logic;
      CAMB_RST_O : out std_logic;
      CAMB_PWDN_O : out std_logic;
      S_AXI_ACLK : in std_logic;
      S_AXI_ARESETN : in std_logic;
      S_AXI_AWADDR : in std_logic_vector((C_S_AXI_ADDR_WIDTH-1) downto 0);
      S_AXI_AWVALID : in std_logic;
      S_AXI_WDATA : in std_logic_vector((C_S_AXI_DATA_WIDTH-1) downto 0);
      S_AXI_WSTRB : in std_logic_vector(((C_S_AXI_DATA_WIDTH/8)-1) downto 0);
      S_AXI_WVALID : in std_logic;
      S_AXI_BREADY : in std_logic;
      S_AXI_ARADDR : in std_logic_vector((C_S_AXI_ADDR_WIDTH-1) downto 0);
      S_AXI_ARVALID : in std_logic;
      S_AXI_RREADY : in std_logic;
      S_AXI_ARREADY : out std_logic;
      S_AXI_RDATA : out std_logic_vector((C_S_AXI_DATA_WIDTH-1) downto 0);
      S_AXI_RRESP : out std_logic_vector(1 downto 0);
      S_AXI_RVALID : out std_logic;
      S_AXI_WREADY : out std_logic;
      S_AXI_BRESP : out std_logic_vector(1 downto 0);
      S_AXI_BVALID : out std_logic;
      S_AXI_AWREADY : out std_logic;
      m_axi_aclk : in std_logic;
      m_axi_aresetn : in std_logic;
      md_error : out std_logic;
      m_axi_arready : in std_logic;
      m_axi_arvalid : out std_logic;
      m_axi_araddr : out std_logic_vector((C_M_AXI_ADDR_WIDTH-1) downto 0);
      m_axi_arlen : out std_logic_vector(7 downto 0);
      m_axi_arsize : out std_logic_vector(2 downto 0);
      m_axi_arburst : out std_logic_vector(1 downto 0);
      m_axi_arprot : out std_logic_vector(2 downto 0);
      m_axi_arcache : out std_logic_vector(3 downto 0);
      m_axi_rready : out std_logic;
      m_axi_rvalid : in std_logic;
      m_axi_rdata : in std_logic_vector((C_M_AXI_DATA_WIDTH-1) downto 0);
      m_axi_rresp : in std_logic_vector(1 downto 0);
      m_axi_rlast : in std_logic;
      m_axi_awready : in std_logic;
      m_axi_awvalid : out std_logic;
      m_axi_awaddr : out std_logic_vector((C_M_AXI_ADDR_WIDTH-1) downto 0);
      m_axi_awlen : out std_logic_vector(7 downto 0);
      m_axi_awsize : out std_logic_vector(2 downto 0);
      m_axi_awburst : out std_logic_vector(1 downto 0);
      m_axi_awprot : out std_logic_vector(2 downto 0);
      m_axi_awcache : out std_logic_vector(3 downto 0);
      m_axi_wready : in std_logic;
      m_axi_wvalid : out std_logic;
      m_axi_wdata : out std_logic_vector((C_M_AXI_DATA_WIDTH-1) downto 0);
      m_axi_wstrb : out std_logic_vector(((C_M_AXI_DATA_WIDTH/8)-1) downto 0);
      m_axi_wlast : out std_logic;
      m_axi_bready : out std_logic;
      m_axi_bvalid : in std_logic;
      m_axi_bresp : in std_logic_vector(1 downto 0)
    );
  end component;

begin

  vmodcam_0 : vmodcam
    generic map (
      DEBUG_EN => 0,
      COLORDEPTH => 16,
      C_S_AXI_DATA_WIDTH => 32,
      C_S_AXI_ADDR_WIDTH => 32,
      C_S_AXI_MIN_SIZE => X"000001ff",
      C_USE_WSTRB => 0,
      C_DPHASE_TIMEOUT => 8,
      C_BASEADDR => X"77C00000",
      C_HIGHADDR => X"77C0FFFF",
      C_FAMILY => "spartan6",
      C_NUM_REG => 5,
      C_NUM_MEM => 1,
      C_SLV_AWIDTH => 32,
      C_SLV_DWIDTH => 32,
      C_M_AXI_ADDR_WIDTH => 32,
      C_M_AXI_DATA_WIDTH => 32,
      C_MAX_BURST_LEN => 16,
      C_NATIVE_DATA_WIDTH => 32,
      C_LENGTH_WIDTH => 12,
      C_ADDR_PIPE_DEPTH => 1
    )
    port map (
      SW_I => SW_I,
      LED_O => LED_O,
      RESET_I => RESET_I,
      CamClk => CamClk,
      CamClk_180 => CamClk_180,
      CAMA_SDA => CAMA_SDA,
      CAMA_SCL => CAMA_SCL,
      CAMA_D_I => CAMA_D_I,
      CAMA_PCLK_I => CAMA_PCLK_I,
      CAMA_MCLK_O => CAMA_MCLK_O,
      CAMA_LV_I => CAMA_LV_I,
      CAMA_FV_I => CAMA_FV_I,
      CAMA_RST_O => CAMA_RST_O,
      CAMA_PWDN_O => CAMA_PWDN_O,
      CAMX_VDDEN_O => CAMX_VDDEN_O,
      CAMB_SDA => CAMB_SDA,
      CAMB_SCL => CAMB_SCL,
      CAMB_D_I => CAMB_D_I,
      CAMB_PCLK_I => CAMB_PCLK_I,
      CAMB_MCLK_O => CAMB_MCLK_O,
      CAMB_LV_I => CAMB_LV_I,
      CAMB_FV_I => CAMB_FV_I,
      CAMB_RST_O => CAMB_RST_O,
      CAMB_PWDN_O => CAMB_PWDN_O,
      S_AXI_ACLK => S_AXI_ACLK,
      S_AXI_ARESETN => S_AXI_ARESETN,
      S_AXI_AWADDR => S_AXI_AWADDR,
      S_AXI_AWVALID => S_AXI_AWVALID,
      S_AXI_WDATA => S_AXI_WDATA,
      S_AXI_WSTRB => S_AXI_WSTRB,
      S_AXI_WVALID => S_AXI_WVALID,
      S_AXI_BREADY => S_AXI_BREADY,
      S_AXI_ARADDR => S_AXI_ARADDR,
      S_AXI_ARVALID => S_AXI_ARVALID,
      S_AXI_RREADY => S_AXI_RREADY,
      S_AXI_ARREADY => S_AXI_ARREADY,
      S_AXI_RDATA => S_AXI_RDATA,
      S_AXI_RRESP => S_AXI_RRESP,
      S_AXI_RVALID => S_AXI_RVALID,
      S_AXI_WREADY => S_AXI_WREADY,
      S_AXI_BRESP => S_AXI_BRESP,
      S_AXI_BVALID => S_AXI_BVALID,
      S_AXI_AWREADY => S_AXI_AWREADY,
      m_axi_aclk => m_axi_aclk,
      m_axi_aresetn => m_axi_aresetn,
      md_error => md_error,
      m_axi_arready => m_axi_arready,
      m_axi_arvalid => m_axi_arvalid,
      m_axi_araddr => m_axi_araddr,
      m_axi_arlen => m_axi_arlen,
      m_axi_arsize => m_axi_arsize,
      m_axi_arburst => m_axi_arburst,
      m_axi_arprot => m_axi_arprot,
      m_axi_arcache => m_axi_arcache,
      m_axi_rready => m_axi_rready,
      m_axi_rvalid => m_axi_rvalid,
      m_axi_rdata => m_axi_rdata,
      m_axi_rresp => m_axi_rresp,
      m_axi_rlast => m_axi_rlast,
      m_axi_awready => m_axi_awready,
      m_axi_awvalid => m_axi_awvalid,
      m_axi_awaddr => m_axi_awaddr,
      m_axi_awlen => m_axi_awlen,
      m_axi_awsize => m_axi_awsize,
      m_axi_awburst => m_axi_awburst,
      m_axi_awprot => m_axi_awprot,
      m_axi_awcache => m_axi_awcache,
      m_axi_wready => m_axi_wready,
      m_axi_wvalid => m_axi_wvalid,
      m_axi_wdata => m_axi_wdata,
      m_axi_wstrb => m_axi_wstrb,
      m_axi_wlast => m_axi_wlast,
      m_axi_bready => m_axi_bready,
      m_axi_bvalid => m_axi_bvalid,
      m_axi_bresp => m_axi_bresp
    );

end architecture STRUCTURE;

