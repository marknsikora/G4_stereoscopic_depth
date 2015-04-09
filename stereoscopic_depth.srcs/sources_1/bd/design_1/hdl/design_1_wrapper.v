//Copyright 1986-2014 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2014.1 (win64) Build 881834 Fri Apr  4 14:15:54 MDT 2014
//Date        : Tue Apr 07 08:10:37 2015
//Host        : WIN-T2LAIKDPBM4 running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (DDR2_addr,
    DDR2_ba,
    DDR2_cas_n,
    DDR2_ck_n,
    DDR2_ck_p,
    DDR2_cke,
    DDR2_cs_n,
    DDR2_dm,
    DDR2_dq,
    DDR2_dqs_n,
    DDR2_dqs_p,
    DDR2_odt,
    DDR2_ras_n,
    DDR2_we_n,
    LED0,
    LED15,
    USB_Uart_rxd,
    USB_Uart_txd,
    ov7670_d,
    ov7670_d_2,
    ov7670_href,
    ov7670_href_2,
    ov7670_pclk,
    ov7670_pclk_2,
    ov7670_pwdn,
    ov7670_pwdn_2,
    ov7670_reset,
    ov7670_reset_2,
    ov7670_sioc,
    ov7670_sioc_2,
    ov7670_siod,
    ov7670_siod_2,
    ov7670_vsync,
    ov7670_vsync_2,
    ov7670_xclk,
    ov7670_xclk_2,
    reset,
    sys_clock,
    vga_blue,
    vga_green,
    vga_hsync,
    vga_red,
    vga_vsync);
  output [12:0]DDR2_addr;
  output [2:0]DDR2_ba;
  output DDR2_cas_n;
  output [0:0]DDR2_ck_n;
  output [0:0]DDR2_ck_p;
  output [0:0]DDR2_cke;
  output [0:0]DDR2_cs_n;
  output [1:0]DDR2_dm;
  inout [15:0]DDR2_dq;
  inout [1:0]DDR2_dqs_n;
  inout [1:0]DDR2_dqs_p;
  output [0:0]DDR2_odt;
  output DDR2_ras_n;
  output DDR2_we_n;
  output LED0;
  output LED15;
  input USB_Uart_rxd;
  output USB_Uart_txd;
  input [7:0]ov7670_d;
  input [7:0]ov7670_d_2;
  input ov7670_href;
  input ov7670_href_2;
  input ov7670_pclk;
  input ov7670_pclk_2;
  output [0:0]ov7670_pwdn;
  output [0:0]ov7670_pwdn_2;
  output ov7670_reset;
  output ov7670_reset_2;
  output ov7670_sioc;
  output ov7670_sioc_2;
  inout ov7670_siod;
  inout ov7670_siod_2;
  input ov7670_vsync;
  input ov7670_vsync_2;
  output ov7670_xclk;
  output ov7670_xclk_2;
  input reset;
  input sys_clock;
  output [3:0]vga_blue;
  output [3:0]vga_green;
  output vga_hsync;
  output [3:0]vga_red;
  output vga_vsync;

  wire [12:0]DDR2_addr;
  wire [2:0]DDR2_ba;
  wire DDR2_cas_n;
  wire [0:0]DDR2_ck_n;
  wire [0:0]DDR2_ck_p;
  wire [0:0]DDR2_cke;
  wire [0:0]DDR2_cs_n;
  wire [1:0]DDR2_dm;
  wire [15:0]DDR2_dq;
  wire [1:0]DDR2_dqs_n;
  wire [1:0]DDR2_dqs_p;
  wire [0:0]DDR2_odt;
  wire DDR2_ras_n;
  wire DDR2_we_n;
  wire LED0;
  wire LED15;
  wire USB_Uart_rxd;
  wire USB_Uart_txd;
  wire [7:0]ov7670_d;
  wire [7:0]ov7670_d_2;
  wire ov7670_href;
  wire ov7670_href_2;
  wire ov7670_pclk;
  wire ov7670_pclk_2;
  wire [0:0]ov7670_pwdn;
  wire [0:0]ov7670_pwdn_2;
  wire ov7670_reset;
  wire ov7670_reset_2;
  wire ov7670_sioc;
  wire ov7670_sioc_2;
  wire ov7670_siod;
  wire ov7670_siod_2;
  wire ov7670_vsync;
  wire ov7670_vsync_2;
  wire ov7670_xclk;
  wire ov7670_xclk_2;
  wire reset;
  wire sys_clock;
  wire [3:0]vga_blue;
  wire [3:0]vga_green;
  wire vga_hsync;
  wire [3:0]vga_red;
  wire vga_vsync;

design_1 design_1_i
       (.DDR2_addr(DDR2_addr),
        .DDR2_ba(DDR2_ba),
        .DDR2_cas_n(DDR2_cas_n),
        .DDR2_ck_n(DDR2_ck_n),
        .DDR2_ck_p(DDR2_ck_p),
        .DDR2_cke(DDR2_cke),
        .DDR2_cs_n(DDR2_cs_n),
        .DDR2_dm(DDR2_dm),
        .DDR2_dq(DDR2_dq),
        .DDR2_dqs_n(DDR2_dqs_n),
        .DDR2_dqs_p(DDR2_dqs_p),
        .DDR2_odt(DDR2_odt),
        .DDR2_ras_n(DDR2_ras_n),
        .DDR2_we_n(DDR2_we_n),
        .LED0(LED0),
        .LED15(LED15),
        .USB_Uart_rxd(USB_Uart_rxd),
        .USB_Uart_txd(USB_Uart_txd),
        .ov7670_d(ov7670_d),
        .ov7670_d_2(ov7670_d_2),
        .ov7670_href(ov7670_href),
        .ov7670_href_2(ov7670_href_2),
        .ov7670_pclk(ov7670_pclk),
        .ov7670_pclk_2(ov7670_pclk_2),
        .ov7670_pwdn(ov7670_pwdn),
        .ov7670_pwdn_2(ov7670_pwdn_2),
        .ov7670_reset(ov7670_reset),
        .ov7670_reset_2(ov7670_reset_2),
        .ov7670_sioc(ov7670_sioc),
        .ov7670_sioc_2(ov7670_sioc_2),
        .ov7670_siod(ov7670_siod),
        .ov7670_siod_2(ov7670_siod_2),
        .ov7670_vsync(ov7670_vsync),
        .ov7670_vsync_2(ov7670_vsync_2),
        .ov7670_xclk(ov7670_xclk),
        .ov7670_xclk_2(ov7670_xclk_2),
        .reset(reset),
        .sys_clock(sys_clock),
        .vga_blue(vga_blue),
        .vga_green(vga_green),
        .vga_hsync(vga_hsync),
        .vga_red(vga_red),
        .vga_vsync(vga_vsync));
endmodule
