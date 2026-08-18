"""
Lab: 2D Convolution — Fixed-Point DMA Streaming
================================================
Verified against: design_1_fixed.bit / design_1_fixed.hwh

Fixed-point format: ap_fixed<16, 3>  (Q3.13)   ← must match fir_common.h
  - Total bits  : 16
  - Integer bits: 3  (signed, so range: -4.0 to +3.99988…)
  - Frac bits   : 13
  - Scale factor: 2^13 = 8192
  - LSB         : 1/8192 ≈ 0.000122

AXI-Lite register map (from design_1_fixed.hwh):
  0x00  CTRL      ap_start / ap_done / ap_idle …
  0x04  GIER
  0x08  IP_IER
  0x0C  IP_ISR
  0x10  rows      (32-bit scalar)
  0x18  cols      (32-bit scalar)
  0x20  kernel[0] (9 × 4-byte words, i.e. kernel[i] at 0x20 + i*4)

IP instance name (from hwh): conv2d_stream_0
DMA instance name           : axi_dma_0
Bitfile                     : design_1_fixed.bit

MAX_WIDTH in HLS = 128, so cols ≤ 128.
DMA buffer limit ~ 16383 bytes  → rows*cols*4 must stay under that.
  Safe choices: 63×64 (16128 B) or any smaller image.
"""

import time
import numpy as np
import matplotlib.pyplot as plt
from pynq import Overlay, allocate
from scipy.signal import convolve2d

# ================================================================
# 0. Fixed-Point Parameters  — must exactly match fir_common.h
#    typedef ap_fixed<16, 3> data_t;
# ================================================================
W     = 16          # total bits
I     = 3           # integer bits (includes sign bit)
F     = W - I       # fractional bits = 13
SCALE = 2 ** F      # 8192

print("=" * 60)
print(f"Fixed-point format : ap_fixed<{W},{I}>  (Q{I}.{F})")
print(f"Scale factor       : 2^{F} = {SCALE}")
print(f"Representable range: [{-2**(I-1):.5f}, {2**(I-1) - 1.0/SCALE:.6f}]")
print(f"Resolution (1 LSB) : {1.0/SCALE:.8f}")
print("=" * 60, "\n")

# ================================================================
# 1. Conversion helpers
# ================================================================

def float_to_q(f: float) -> int:
    """
    Float → ap_fixed<16,3> as a 16-bit two's-complement value
    zero-extended to 32 bits (safe for PYNQ .write() and int32 buffers).

    Clamps to the representable range to catch overflow before writing.
    """
    max_val =  2**(I-1) - 1.0/SCALE   #  3.99988…
    min_val = -2**(I-1)                # -4.0
    if f > max_val or f < min_val:
        raise OverflowError(
            f"Value {f:.6f} is outside ap_fixed<{W},{I}> range "
            f"[{min_val}, {max_val:.5f}]"
        )
    val = int(round(f * SCALE))
    return val & 0xFFFF  # return unsigned 16-bit (two's complement)


def q_to_float(raw32: int) -> float:
    """
    Raw 32-bit DMA output → float.
    Lower 16 bits hold the ap_fixed<16,3> result in two's complement.
    np.int16() restores the sign bit before dividing by SCALE.
    """
    return float(np.int16(raw32 & 0xFFFF)) / SCALE


# ── Sanity checks ────────────────────────────────────────────────
assert float_to_q( 1.0)  == 0x1000 * (SCALE // 4096), \
    f"Expected {hex(SCALE//4096 * 0x1000)}, got {hex(float_to_q(1.0))}"
assert float_to_q(-1.0)  == ((-1 * SCALE) & 0xFFFF)
assert abs(q_to_float(float_to_q(0.5)) - 0.5) < 1.0/SCALE
print("Conversion sanity checks passed.\n")

# ================================================================
# 2. Load Overlay
# ================================================================
ol = Overlay("design_1_fixed.bit")
print("Overlay loaded:", list(ol.ip_dict.keys()))

dma    = ol.axi_dma_0
conv2d = ol.conv2d_stream_0        # verified from hwh INSTANCE field

print(f"DMA max transfer size : {dma.recvchannel._max_size} bytes\n")

# ================================================================
# 3. Image and Kernel
# ================================================================
# DMA hard limit: 16 383 bytes  → rows*cols*4 ≤ 16383
# 63×64 = 4 032 samples × 4 B = 16 128 B  ✓
ROWS = 63
COLS = 64

# Synthetic image: block in centre, values in [0.0, 1.0]
# ap_fixed<16,3> range is ±4, so 0–1 images are well inside range.
image_in = np.zeros((ROWS, COLS), dtype=np.float32)
image_in[10:40, 10:40] = 1.0

# ── Kernel design ────────────────────────────────────────────────
# Edge-detect kernel (unscaled centre = 8) with a [0,1] image gives
# a worst-case output of 8 × 1.0 = 8.0 → overflows ap_fixed<16,3>.
# Scale kernel by 0.25 → max output = 2.0, well inside [-4, +4).
#
# To use the unscaled kernel you would need ap_fixed<16,5> or images
# normalised to ≤ 0.5.
KERNEL_SCALE = 0.25
kernel_3x3 = KERNEL_SCALE * np.array([
    [-1, -1, -1],
    [-1,  8, -1],
    [-1, -1, -1]
], dtype=np.float32)

print(f"Kernel (scaled ×{KERNEL_SCALE}):\n{kernel_3x3}")
print(f"Kernel value range : [{kernel_3x3.min():.4f}, {kernel_3x3.max():.4f}]")

# Guard: every kernel value must fit in ap_fixed<16,3>
for idx, v in enumerate(kernel_3x3.flatten()):
    float_to_q(v)   # raises OverflowError if out of range
print("Kernel range OK for ap_fixed<16,3>.\n")

# ================================================================
# 4. AXI-Lite Register Map  (from design_1_fixed.hwh)
# ================================================================
CTRL_OFFSET   = 0x00   # ap_start bit[0]
ROWS_OFFSET   = 0x10   # 'rows'     register  (decimal 16)
COLS_OFFSET   = 0x18   # 'cols'     register  (decimal 24)
KERNEL_BASE   = 0x20   # 'Memory_kernel[0]'   (decimal 32)
#                         kernel[i] at KERNEL_BASE + i*4

conv2d.write(ROWS_OFFSET, ROWS)
conv2d.write(COLS_OFFSET, COLS)

kernel_flat = kernel_3x3.flatten()
for i, val in enumerate(kernel_flat):
    conv2d.write(KERNEL_BASE + i * 4, float_to_q(val))

# ── Readback verification (kernel centre element = index 4) ──────
centre_expected = KERNEL_SCALE * 8
rb_raw   = conv2d.read(KERNEL_BASE + 4 * 4)
rb_float = q_to_float(rb_raw)
print(f"Kernel[4] readback : raw=0x{rb_raw:04X}  float={rb_float:.5f}"
      f"  (expected {centre_expected:.5f})")
if abs(rb_float - centre_expected) < 2.0 / SCALE:
    print("  ✅  Kernel readback OK")
else:
    print("  ⚠️  Kernel readback mismatch — check register offset or fixed-point format")
print(f"\nIP configured for {ROWS}×{COLS} image.\n")

# ================================================================
# 5. DMA Buffers — dtype=int32 (each sample in lower 16 bits)
# ================================================================
n_pixels = ROWS * COLS
in_buf   = allocate(shape=(n_pixels,), dtype=np.int32)
out_buf  = allocate(shape=(n_pixels,), dtype=np.int32)

buf_bytes = in_buf.nbytes
assert buf_bytes <= dma.recvchannel._max_size, (
    f"Buffer {buf_bytes} B exceeds DMA limit "
    f"{dma.recvchannel._max_size} B — reduce ROWS or COLS")

# Pack image into Q3.13 fixed-point
image_flat = image_in.flatten()
for idx, px in enumerate(image_flat):
    in_buf[idx] = float_to_q(px)
out_buf[:] = 0

print(f"Buffer size       : {buf_bytes} bytes  ({n_pixels} × int32)")
print(f"in_buf[0]         : 0x{in_buf[0]:04X}  (black pixel, expected 0)")
sample_idx = 10 * COLS + 10
print(f"in_buf[10×COLS+10]: 0x{in_buf[sample_idx]:04X}"
      f"  = {q_to_float(int(in_buf[sample_idx])):.5f}  (expected 1.00000)")

# ================================================================
# 6. DMA Transfer + IP Start
# ================================================================
print("\n--- Starting DMA Transfer ---")
t0 = time.perf_counter()

dma.recvchannel.transfer(out_buf)   # arm S2MM (receive) FIRST
dma.sendchannel.transfer(in_buf)    # then MM2S (send)
conv2d.write(CTRL_OFFSET, 0x01)     # ap_start

dma.sendchannel.wait()
dma.recvchannel.wait()

t_dma = time.perf_counter() - t0
print(f"DMA complete : {n_pixels} pixels in {t_dma*1e3:.3f} ms\n")

# ================================================================
# 7. Dequantise Output
# ================================================================
raw_out      = np.array(out_buf, dtype=np.int32)
hw_int16     = raw_out.astype(np.int16)                     # restore sign
image_out_hw = hw_int16.astype(np.float32) / SCALE
image_out_hw = image_out_hw.reshape((ROWS, COLS))

print(f"HW output range : [{image_out_hw.min():.5f}, {image_out_hw.max():.5f}]")
print(f"Non-zero pixels : {np.count_nonzero(image_out_hw)} / {n_pixels}")

in_buf.freebuffer()
out_buf.freebuffer()

# ================================================================
# 8. Verification vs Software Golden Model
# ================================================================
# Use the identical scaled kernel and same 'same'/'fill' boundary
image_out_sw = convolve2d(
    image_in, kernel_3x3, mode='same', boundary='fill', fillvalue=0
).astype(np.float32)

max_diff  = np.max (np.abs(image_out_hw - image_out_sw))
mean_diff = np.mean(np.abs(image_out_hw - image_out_sw))

# Worst-case quantisation error: 9 taps × 0.5 LSB per mul ≈ 4.5 LSBs
TOLERANCE = 10.0 / SCALE    # 10 LSBs generous headroom

print(f"\nMax  |HW − SW| = {max_diff:.7f}  (tolerance = {TOLERANCE:.7f})")
print(f"Mean |HW − SW| = {mean_diff:.7f}")
print(f"1 LSB          = {1.0/SCALE:.7f}")

if max_diff <= TOLERANCE:
    print("✅  PASS: Hardware matches software within quantisation bounds!")
else:
    print("⚠️  FAIL: Outputs exceed quantisation error threshold.")
    print("    Possible causes: wrong register offsets, wrong fixed-point format,")
    print("    or TLAST not received (out_buf zeros).")

# ================================================================
# 9. Visualisation
# ================================================================
fig, axes = plt.subplots(1, 3, figsize=(15, 5))
axes[0].imshow(image_in,     cmap='gray', vmin=image_in.min(),     vmax=image_in.max())
axes[0].set_title("Input Image")
axes[1].imshow(image_out_sw, cmap='gray', vmin=image_out_sw.min(), vmax=image_out_sw.max())
axes[1].set_title(f"SW Output (SciPy,  ×{KERNEL_SCALE})")
axes[2].imshow(image_out_hw, cmap='gray', vmin=image_out_sw.min(), vmax=image_out_sw.max())
axes[2].set_title(f"HW Output (Q{I}.{F}, ×{KERNEL_SCALE})")
for ax in axes:
    ax.axis('off')
plt.tight_layout()
plt.savefig("conv2d_result.png", dpi=120)
plt.show()

# ── Error heatmap ─────────────────────────────────────────────────
diff_map = np.abs(image_out_hw - image_out_sw)
fig2, ax2 = plt.subplots(figsize=(6, 5))
im = ax2.imshow(diff_map, cmap='hot')
ax2.set_title(
    f"|HW − SW|  max={max_diff:.5f}  1LSB={1/SCALE:.5f}"
)
plt.colorbar(im, ax=ax2)
ax2.axis('off')
plt.tight_layout()
plt.savefig("conv2d_error.png", dpi=120)
plt.show()
