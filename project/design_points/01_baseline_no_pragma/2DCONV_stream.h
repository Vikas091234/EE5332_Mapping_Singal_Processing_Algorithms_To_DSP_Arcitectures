#ifndef FIR_STREAM_H
#define FIR_STREAM_H

#include "fir_common.h"
#include <hls_stream.h>
#include <ap_axi_sdata.h>

/* 32-bit AXI-Stream packet with TLAST.
 * Side-channels (TUSER, TID, TDEST) set to width 1. */
typedef ap_axis<32, 1, 1, 1> axis_pkt_t;

/*
 * Streaming FIR filter.
 *   in_stream  : AXI-Stream input  (connect to DMA S2MM or MM2S)
 *   out_stream : AXI-Stream output (connect to DMA)
 *   n          : number of samples to process (set via AXI-Lite)
 *
 * The filter maintains internal shift-register state across calls
 * (static storage), so consecutive invocations continue where the
 * previous one left off.
 */
void conv2d_stream(hls::stream<axis_pkt_t> &in_stream,
                   hls::stream<axis_pkt_t> &out_stream,
                   int rows, int cols,
                   float kernel[9]);
#endif
