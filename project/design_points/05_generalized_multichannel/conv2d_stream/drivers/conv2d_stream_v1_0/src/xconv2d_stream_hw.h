// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// CTRL
// 0x0000 : Control signals
//          bit 0  - ap_start (Read/Write/COH)
//          bit 1  - ap_done (Read/COR)
//          bit 2  - ap_idle (Read)
//          bit 3  - ap_ready (Read/COR)
//          bit 7  - auto_restart (Read/Write)
//          others - reserved
// 0x0004 : Global Interrupt Enable Register
//          bit 0  - Global Interrupt Enable (Read/Write)
//          others - reserved
// 0x0008 : IP Interrupt Enable Register (Read/Write)
//          bit 0  - enable ap_done interrupt (Read/Write)
//          bit 1  - enable ap_ready interrupt (Read/Write)
//          others - reserved
// 0x000c : IP Interrupt Status Register (Read/TOW)
//          bit 0  - ap_done (COR/TOW)
//          bit 1  - ap_ready (COR/TOW)
//          others - reserved
// 0x0010 : Data signal of rows
//          bit 31~0 - rows[31:0] (Read/Write)
// 0x0014 : reserved
// 0x0018 : Data signal of cols
//          bit 31~0 - cols[31:0] (Read/Write)
// 0x001c : reserved
// 0x0020 : Data signal of Cin
//          bit 31~0 - Cin[31:0] (Read/Write)
// 0x0024 : reserved
// 0x0028 : Data signal of Cout
//          bit 31~0 - Cout[31:0] (Read/Write)
// 0x002c : reserved
// 0x1000 ~
// 0x1fff : Memory 'kernel' (576 * 32b)
//          Word n : bit [31:0] - kernel[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XCONV2D_STREAM_CTRL_ADDR_AP_CTRL     0x0000
#define XCONV2D_STREAM_CTRL_ADDR_GIE         0x0004
#define XCONV2D_STREAM_CTRL_ADDR_IER         0x0008
#define XCONV2D_STREAM_CTRL_ADDR_ISR         0x000c
#define XCONV2D_STREAM_CTRL_ADDR_ROWS_DATA   0x0010
#define XCONV2D_STREAM_CTRL_BITS_ROWS_DATA   32
#define XCONV2D_STREAM_CTRL_ADDR_COLS_DATA   0x0018
#define XCONV2D_STREAM_CTRL_BITS_COLS_DATA   32
#define XCONV2D_STREAM_CTRL_ADDR_CIN_DATA    0x0020
#define XCONV2D_STREAM_CTRL_BITS_CIN_DATA    32
#define XCONV2D_STREAM_CTRL_ADDR_COUT_DATA   0x0028
#define XCONV2D_STREAM_CTRL_BITS_COUT_DATA   32
#define XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE 0x1000
#define XCONV2D_STREAM_CTRL_ADDR_KERNEL_HIGH 0x1fff
#define XCONV2D_STREAM_CTRL_WIDTH_KERNEL     32
#define XCONV2D_STREAM_CTRL_DEPTH_KERNEL     576

