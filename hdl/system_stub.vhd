-------------------------------------------------------------------------------
-- system_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system_stub is
  port (
    zio : inout std_logic;
    rzq : inout std_logic;
    mcbx_dram_we_n : out std_logic;
    mcbx_dram_udqs_n : inout std_logic;
    mcbx_dram_udqs : inout std_logic;
    mcbx_dram_udm : out std_logic;
    mcbx_dram_ras_n : out std_logic;
    mcbx_dram_odt : out std_logic;
    mcbx_dram_ldm : out std_logic;
    mcbx_dram_dqs_n : inout std_logic;
    mcbx_dram_dqs : inout std_logic;
    mcbx_dram_dq : inout std_logic_vector(15 downto 0);
    mcbx_dram_clk_n : out std_logic;
    mcbx_dram_clk : out std_logic;
    mcbx_dram_cke : out std_logic;
    mcbx_dram_cas_n : out std_logic;
    mcbx_dram_ba : out std_logic_vector(2 downto 0);
    mcbx_dram_addr : out std_logic_vector(12 downto 0);
    RS232_Uart_1_sout : out std_logic;
    RS232_Uart_1_sin : in std_logic;
    RESET : in std_logic;
    GCLK : in std_logic;
    hdmi_out_0_TMDS_pin : out std_logic_vector(3 downto 0);
    hdmi_out_0_TMDSB_pin : out std_logic_vector(3 downto 0);
    CAMA_LV_I : inout std_logic;
    CAMB_PWDN_O : out std_logic;
    CAMB_LV_I : inout std_logic;
    CAMB_FV_I : inout std_logic;
    CAMB_RST_O : out std_logic;
    CAMB_D_I : inout std_logic_vector(7 downto 0);
    CAMB_PCLK_I : inout std_logic;
    CAMB_MCLK_O : out std_logic;
    CAMX_VDDEN_O : out std_logic;
    CAMB_SDA : inout std_logic;
    CAMB_SCL : inout std_logic;
    CAMA_FV_I : inout std_logic;
    CAMA_RST_O : out std_logic;
    CAMA_PWDN_O : out std_logic;
    CAMA_SCL : inout std_logic;
    CAMA_D_I : inout std_logic_vector(7 downto 0);
    CAMA_PCLK_I : inout std_logic;
    CAMA_SDA : inout std_logic;
    CAMA_MCLK_O : out std_logic;
    SW_I : in std_logic_vector(7 downto 0);
    LED_O : out std_logic_vector(7 downto 0)
  );
end system_stub;

architecture STRUCTURE of system_stub is

  component system is
    port (
      zio : inout std_logic;
      rzq : inout std_logic;
      mcbx_dram_we_n : out std_logic;
      mcbx_dram_udqs_n : inout std_logic;
      mcbx_dram_udqs : inout std_logic;
      mcbx_dram_udm : out std_logic;
      mcbx_dram_ras_n : out std_logic;
      mcbx_dram_odt : out std_logic;
      mcbx_dram_ldm : out std_logic;
      mcbx_dram_dqs_n : inout std_logic;
      mcbx_dram_dqs : inout std_logic;
      mcbx_dram_dq : inout std_logic_vector(15 downto 0);
      mcbx_dram_clk_n : out std_logic;
      mcbx_dram_clk : out std_logic;
      mcbx_dram_cke : out std_logic;
      mcbx_dram_cas_n : out std_logic;
      mcbx_dram_ba : out std_logic_vector(2 downto 0);
      mcbx_dram_addr : out std_logic_vector(12 downto 0);
      RS232_Uart_1_sout : out std_logic;
      RS232_Uart_1_sin : in std_logic;
      RESET : in std_logic;
      GCLK : in std_logic;
      hdmi_out_0_TMDS_pin : out std_logic_vector(3 downto 0);
      hdmi_out_0_TMDSB_pin : out std_logic_vector(3 downto 0);
      CAMA_LV_I : inout std_logic;
      CAMB_PWDN_O : out std_logic;
      CAMB_LV_I : inout std_logic;
      CAMB_FV_I : inout std_logic;
      CAMB_RST_O : out std_logic;
      CAMB_D_I : inout std_logic_vector(7 downto 0);
      CAMB_PCLK_I : inout std_logic;
      CAMB_MCLK_O : out std_logic;
      CAMX_VDDEN_O : out std_logic;
      CAMB_SDA : inout std_logic;
      CAMB_SCL : inout std_logic;
      CAMA_FV_I : inout std_logic;
      CAMA_RST_O : out std_logic;
      CAMA_PWDN_O : out std_logic;
      CAMA_SCL : inout std_logic;
      CAMA_D_I : inout std_logic_vector(7 downto 0);
      CAMA_PCLK_I : inout std_logic;
      CAMA_SDA : inout std_logic;
      CAMA_MCLK_O : out std_logic;
      SW_I : in std_logic_vector(7 downto 0);
      LED_O : out std_logic_vector(7 downto 0)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";

begin

  system_i : system
    port map (
      zio => zio,
      rzq => rzq,
      mcbx_dram_we_n => mcbx_dram_we_n,
      mcbx_dram_udqs_n => mcbx_dram_udqs_n,
      mcbx_dram_udqs => mcbx_dram_udqs,
      mcbx_dram_udm => mcbx_dram_udm,
      mcbx_dram_ras_n => mcbx_dram_ras_n,
      mcbx_dram_odt => mcbx_dram_odt,
      mcbx_dram_ldm => mcbx_dram_ldm,
      mcbx_dram_dqs_n => mcbx_dram_dqs_n,
      mcbx_dram_dqs => mcbx_dram_dqs,
      mcbx_dram_dq => mcbx_dram_dq,
      mcbx_dram_clk_n => mcbx_dram_clk_n,
      mcbx_dram_clk => mcbx_dram_clk,
      mcbx_dram_cke => mcbx_dram_cke,
      mcbx_dram_cas_n => mcbx_dram_cas_n,
      mcbx_dram_ba => mcbx_dram_ba,
      mcbx_dram_addr => mcbx_dram_addr,
      RS232_Uart_1_sout => RS232_Uart_1_sout,
      RS232_Uart_1_sin => RS232_Uart_1_sin,
      RESET => RESET,
      GCLK => GCLK,
      hdmi_out_0_TMDS_pin => hdmi_out_0_TMDS_pin,
      hdmi_out_0_TMDSB_pin => hdmi_out_0_TMDSB_pin,
      CAMA_LV_I => CAMA_LV_I,
      CAMB_PWDN_O => CAMB_PWDN_O,
      CAMB_LV_I => CAMB_LV_I,
      CAMB_FV_I => CAMB_FV_I,
      CAMB_RST_O => CAMB_RST_O,
      CAMB_D_I => CAMB_D_I,
      CAMB_PCLK_I => CAMB_PCLK_I,
      CAMB_MCLK_O => CAMB_MCLK_O,
      CAMX_VDDEN_O => CAMX_VDDEN_O,
      CAMB_SDA => CAMB_SDA,
      CAMB_SCL => CAMB_SCL,
      CAMA_FV_I => CAMA_FV_I,
      CAMA_RST_O => CAMA_RST_O,
      CAMA_PWDN_O => CAMA_PWDN_O,
      CAMA_SCL => CAMA_SCL,
      CAMA_D_I => CAMA_D_I,
      CAMA_PCLK_I => CAMA_PCLK_I,
      CAMA_SDA => CAMA_SDA,
      CAMA_MCLK_O => CAMA_MCLK_O,
      SW_I => SW_I,
      LED_O => LED_O
    );

end architecture STRUCTURE;

