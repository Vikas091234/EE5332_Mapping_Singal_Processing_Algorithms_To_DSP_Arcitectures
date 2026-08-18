// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xconv2d_optimized.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XConv2d_optimized_CfgInitialize(XConv2d_optimized *InstancePtr, XConv2d_optimized_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XConv2d_optimized_Start(XConv2d_optimized *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_AP_CTRL) & 0x80;
    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XConv2d_optimized_IsDone(XConv2d_optimized *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XConv2d_optimized_IsIdle(XConv2d_optimized *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XConv2d_optimized_IsReady(XConv2d_optimized *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XConv2d_optimized_EnableAutoRestart(XConv2d_optimized *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XConv2d_optimized_DisableAutoRestart(XConv2d_optimized *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_AP_CTRL, 0);
}

void XConv2d_optimized_Set_rows(XConv2d_optimized *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_ROWS_DATA, Data);
}

u32 XConv2d_optimized_Get_rows(XConv2d_optimized *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_ROWS_DATA);
    return Data;
}

void XConv2d_optimized_Set_cols(XConv2d_optimized *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_COLS_DATA, Data);
}

u32 XConv2d_optimized_Get_cols(XConv2d_optimized *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_COLS_DATA);
    return Data;
}

u32 XConv2d_optimized_Get_kernel_BaseAddress(XConv2d_optimized *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE);
}

u32 XConv2d_optimized_Get_kernel_HighAddress(XConv2d_optimized *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_HIGH);
}

u32 XConv2d_optimized_Get_kernel_TotalBytes(XConv2d_optimized *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_HIGH - XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE + 1);
}

u32 XConv2d_optimized_Get_kernel_BitWidth(XConv2d_optimized *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCONV2D_OPTIMIZED_CONTROL_WIDTH_KERNEL;
}

u32 XConv2d_optimized_Get_kernel_Depth(XConv2d_optimized *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCONV2D_OPTIMIZED_CONTROL_DEPTH_KERNEL;
}

u32 XConv2d_optimized_Write_kernel_Words(XConv2d_optimized *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_HIGH - XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XConv2d_optimized_Read_kernel_Words(XConv2d_optimized *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_HIGH - XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE + (offset + i)*4);
    }
    return length;
}

u32 XConv2d_optimized_Write_kernel_Bytes(XConv2d_optimized *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_HIGH - XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XConv2d_optimized_Read_kernel_Bytes(XConv2d_optimized *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_HIGH - XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XCONV2D_OPTIMIZED_CONTROL_ADDR_KERNEL_BASE + offset + i);
    }
    return length;
}

void XConv2d_optimized_InterruptGlobalEnable(XConv2d_optimized *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_GIE, 1);
}

void XConv2d_optimized_InterruptGlobalDisable(XConv2d_optimized *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_GIE, 0);
}

void XConv2d_optimized_InterruptEnable(XConv2d_optimized *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_IER);
    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_IER, Register | Mask);
}

void XConv2d_optimized_InterruptDisable(XConv2d_optimized *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_IER);
    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_IER, Register & (~Mask));
}

void XConv2d_optimized_InterruptClear(XConv2d_optimized *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConv2d_optimized_WriteReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_ISR, Mask);
}

u32 XConv2d_optimized_InterruptGetEnabled(XConv2d_optimized *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_IER);
}

u32 XConv2d_optimized_InterruptGetStatus(XConv2d_optimized *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XConv2d_optimized_ReadReg(InstancePtr->Control_BaseAddress, XCONV2D_OPTIMIZED_CONTROL_ADDR_ISR);
}

