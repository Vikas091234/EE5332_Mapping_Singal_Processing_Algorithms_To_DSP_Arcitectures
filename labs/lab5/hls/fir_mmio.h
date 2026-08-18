#ifndef FIR_MMIO_H
#define FIR_MMIO_H

#include "fir_common.h"

/*
 * MMIO (AXI-Lite) FIR filter.
 * Processes one sample per invocation.  Caller writes x_in, starts the
 * IP, waits for ap_done, and reads the return value.
 *
 * This version exists to demonstrate the overhead of per-sample
 * PS-PL round-trips compared to the DMA/streaming approach.
 */
data_t fir_mmio(data_t x_in);

#endif
