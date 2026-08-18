#ifndef FIR_COMMON_H
#define FIR_COMMON_H

/*
 * FIR filter common definitions for Lab 5.
 *
 * Data type configuration:
 *   Define USE_FLOAT for 32-bit float, or USE_FIXED for ap_fixed.
 *   Default is float.  When switching to fixed-point, also update
 *   DATA_WIDTH and the Python/Pynq side accordingly.
 */

/* ---- Choose one ---- */
/*#define USE_FLOAT*/
#define USE_FIXED 

#ifdef USE_FIXED
#include <ap_fixed.h>
typedef ap_fixed<16, 4> data_t;
#define DATA_WIDTH 16
#else
typedef float data_t;
#define DATA_WIDTH 32
#endif

#include "fir_coeffs.h"   /* N_TAPS, coeffs[] */

#endif
