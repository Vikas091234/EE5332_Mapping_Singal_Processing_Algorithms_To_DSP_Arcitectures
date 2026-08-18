// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xconv2d_stream.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XConv2d_stream_CfgInitialize(XConv2d_stream *InstancePtr, XConv2d_stream_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XConv2d_stream_Start(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL) & 0x80;
    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XConv2d_stream_IsDone(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XConv2d_stream_IsIdle(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XConv2d_stream_IsReady(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XConv2d_stream_EnableAutoRestart(XConv2d_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL, 0x80);
}

void XConv2d_stream_DisableAutoRestart(XConv2d_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_AP_CTRL, 0);
}

void XConv2d_stream_Set_rows(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_ROWS_DATA, Data);
}

u32 XConv2d_stream_Get_rows(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_ROWS_DATA);
    return Data;
}

void XConv2d_stream_Set_cols(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_COLS_DATA, Data);
}

u32 XConv2d_stream_Get_cols(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_COLS_DATA);
    return Data;
}

void XConv2d_stream_Set_Cin(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_CIN_DATA, Data);
}

u32 XConv2d_stream_Get_Cin(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_CIN_DATA);
    return Data;
}

void XConv2d_stream_Set_Cout(XConv2d_stream *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_COUT_DATA, Data);
}

u32 XConv2d_stream_Get_Cout(XConv2d_stream *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_COUT_DATA);
    return Data;
}

u32 XConv2d_stream_Get_kernel_BaseAddress(XConv2d_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Ctrl_BaseAddress + XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE);
}

u32 XConv2d_stream_Get_kernel_HighAddress(XConv2d_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Ctrl_BaseAddress + XCONV2D_STREAM_CTRL_ADDR_KERNEL_HIGH);
}

u32 XConv2d_stream_Get_kernel_TotalBytes(XConv2d_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XCONV2D_STREAM_CTRL_ADDR_KERNEL_HIGH - XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE + 1);
}

u32 XConv2d_stream_Get_kernel_BitWidth(XConv2d_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCONV2D_STREAM_CTRL_WIDTH_KERNEL;
}

u32 XConv2d_stream_Get_kernel_Depth(XConv2d_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCONV2D_STREAM_CTRL_DEPTH_KERNEL;
}

u32 XConv2d_stream_Write_kernel_Words(XConv2d_stream *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XCONV2D_STREAM_CTRL_ADDR_KERNEL_HIGH - XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Ctrl_BaseAddress + XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XConv2d_stream_Read_kernel_Words(XConv2d_stream *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XCONV2D_STREAM_CTRL_ADDR_KERNEL_HIGH - XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Ctrl_BaseAddress + XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE + (offset + i)*4);
    }
    return length;
}

u32 XConv2d_stream_Write_kernel_Bytes(XConv2d_stream *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XCONV2D_STREAM_CTRL_ADDR_KERNEL_HIGH - XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Ctrl_BaseAddress + XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XConv2d_stream_Read_kernel_Bytes(XConv2d_stream *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XCONV2D_STREAM_CTRL_ADDR_KERNEL_HIGH - XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Ctrl_BaseAddress + XCONV2D_STREAM_CTRL_ADDR_KERNEL_BASE + offset + i);
    }
    return length;
}

void XConv2d_stream_InterruptGlobalEnable(XConv2d_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_GIE, 1);
}

void XConv2d_stream_InterruptGlobalDisable(XConv2d_stream *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_GIE, 0);
}

void XConv2d_stream_InterruptEnable(XConv2d_stream *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER);
    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER, Register | Mask);
}

void XConv2d_stream_InterruptDisable(XConv2d_stream *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER);
    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER, Register & (~Mask));
}

void XConv2d_stream_InterruptClear(XConv2d_stream *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_stream_WriteReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_ISR, Mask);
}

u32 XConv2d_stream_InterruptGetEnabled(XConv2d_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_IER);
}

u32 XConv2d_stream_InterruptGetStatus(XConv2d_stream *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XConv2d_stream_ReadReg(InstancePtr->Ctrl_BaseAddress, XCONV2D_STREAM_CTRL_ADDR_ISR);
}

