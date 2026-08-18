"""
Lab: 2D Convolution -- DMA Streaming
====================================
"""

import time
import struct
import numpy as np
from pynq import Overlay, allocate
from scipy.signal import convolve2d

# ----------------------------------------------------------------
# 1. Load overlay
# ----------------------------------------------------------------
# Make sure "design_1_float.bit" and "design_1_float.hwh" are in the same folder
ol = Overlay("design_1_float.bit")
print("Overlay loaded successfully")

dma    = ol.axi_dma_0
conv2d = ol.conv2d_stream_0  # FIXED: Matches the IP dictionary name

# ----------------------------------------------------------------
# 2. Prepare test data
# ----------------------------------------------------------------
ROWS = 64
COLS = 64

# Generate a random test image
image_in = np.random.rand(ROWS, COLS).astype(np.float32)

# Define a 3x3 Edge Detection Kernel
kernel_3x3 = np.array([
    [-1, -1, -1],
    [-1,  8, -1],
    [-1, -1, -1]
], dtype=np.float32)

# ----------------------------------------------------------------
# 3. Configure IP via AXI-Lite
# ----------------------------------------------------------------
CTRL_REG     = 0x00
ROWS_OFFSET  = 0x10
COLS_OFFSET  = 0x18
KERNEL_BASE  = 0x40  # FIXED: Dec 64 = Hex 0x40 based on the .hwh file

def float_to_uint(f):
    """Packs a Python float into a 32-bit unsigned integer for MMIO."""
    return struct.unpack('<I', struct.pack('<f', f))[0]

# Write scalars
conv2d.write(ROWS_OFFSET, ROWS)
conv2d.write(COLS_OFFSET, COLS)

# Write 3x3 Kernel array into IP's local memory mapped via AXI-Lite
kernel_flat = kernel_3x3.flatten()
for i, val in enumerate(kernel_flat):
    # Each 32-bit float is 4 bytes apart
    addr = KERNEL_BASE + (i * 4)
    conv2d.write(addr, float_to_uint(val))

print(f"IP configured for {ROWS}x{COLS} image with 3x3 kernel.")

# ----------------------------------------------------------------
# 4. DMA Streaming 
# ----------------------------------------------------------------
# Allocate contiguous buffers for DMA
in_buf  = allocate(shape=(ROWS * COLS,), dtype=np.float32)
out_buf = allocate(shape=(ROWS * COLS,), dtype=np.float32)

# Copy 2D image into flattened 1D DMA buffer
np.copyto(in_buf, image_in.flatten())
out_buf[:] = 0

print("\n--- Starting DMA Transfer ---")
t_start = time.perf_counter()

# FIXED DMA ORDER: Prevent AXI-Stream deadlock by prepping receiver first
dma.recvchannel.transfer(out_buf)
dma.sendchannel.transfer(in_buf)

# Start the IP
conv2d.write(CTRL_REG, 0x01) # ap_start

# Wait for completion
dma.sendchannel.wait()
dma.recvchannel.wait()

t_dma = time.perf_counter() - t_start
print(f"DMA Transfer Complete: {ROWS*COLS} pixels in {t_dma*1e3:.2f} ms")

# ----------------------------------------------------------------
# 5. Verification
# ----------------------------------------------------------------
# Reshape DMA output back to 2D
image_out_hw = np.array(out_buf).reshape((ROWS, COLS))

# Golden model using SciPy
image_out_sw = convolve2d(image_in, kernel_3x3, mode='same', boundary='fill', fillvalue=0)

hw_valid = image_out_hw        # full ROWS x COLS
sw_valid = image_out_sw        # full ROWS x COLS

max_diff = np.max(np.abs(hw_valid - sw_valid))
print(f"Max |HW - SW| (full image) = {max_diff:.2e}")

if max_diff < 1e-4:
    print("PASS: Hardware matches scipy convolve2d with zero padding!")
else:
    print("WARNING: Outputs differ.")

# Cleanup
in_buf.freebuffer()
out_buf.freebuffer()