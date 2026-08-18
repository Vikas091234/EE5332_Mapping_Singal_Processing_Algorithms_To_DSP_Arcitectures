# EE5332 — 2D Convolution Accelerator on FPGA
**EE19B108 — R. Vikas Raj**

Project 3 from the EE5332 (Mapping Signal Processing Algorithms to DSP Architectures)
mini-project list (`project-statements.pdf`): a K×K convolution accelerator (K = 3 or 5)
for a grayscale/RGB image, streamed row-by-row over AXI-Stream, built with a
line-buffer + sliding-window HLS pattern, wrapped for AXI-Stream/DMA, and validated
on a PYNQ board against a NumPy/SciPy software reference.

---

## Repository layout

```
.
├── README.md
├── project-statements.pdf        assignment brief (this is Project 3)
├── report/                       written deliverables
├── src/                          baseline / reference C++ sources
├── design_points/                the 5 explored design points (see below)
└── synthesis_reports/            isolated float-vs-fixed HLS comparison
```

### `report/`

| File | What it is |
|---|---|
| `EE19B108_Report2_Project_Report.docx` | **The project report.** Design choices, Pareto tradeoffs, and the hardware validation results (Table 5 below comes from here). |
| `EE19B108_Report1_Sliding_Window.docx` | Supplementary write-up: a code walkthrough of the line-buffer + sliding-window implementation (`conv2d_optimized` / `conv2d_stream`). |
| `line_buffer_sliding_window_stepper.html`, `..._1.html` | Interactive step-through visualizations of the sliding-window mechanism — open directly in a browser. Companion to Report 1. |

### `src/`

Reference/starting-point C++ sources: `baselinecode.cpp/.h` (software baseline),
`baseline2.cpp`, `rbg.cpp` (RGB variant), `2DCONV5stream.cpp`, `test_bench.cpp`, and
shared headers (`2DCONV_stream.h`, `fir_common.h`). Each `design_points/*/` folder
took a working copy of the relevant files here and adapted it for that specific
variant — treat `src/` as the reference point, not as byte-identical to what's
actually synthesized in each design point.

---

## Design points

Five design points were carried through HLS → Vivado → PYNQ, per the "explore ≥3
points on the Pareto curve" requirement. Numbers are measured on hardware
(PYNQ, wall-clock via `perf_counter`), not HLS-estimated:

| # | Folder | Configuration | Image | Frame time | \|HW−SW\| error | Status |
|---|---|---|---|---|---|---|
| 01 | `01_baseline_no_pragma` | streaming, unpartitioned 3×3, float (target II=9) | 4096 px | 15.72 ms | 7.15e-07 | PASS |
| 02 | `02_float_pipelined_3x3` | pipelined + unrolled 3×3, float | 4096 px | 3.88 ms | 7.15e-07 | PASS |
| 03 | `03_fixed_pipelined_3x3` | streaming, fixed-point 3×3, `ap_fixed<16,3>` | 4096 px | 3.75 ms | 2.5e-04 | PASS |
| 04 | `04_float_pipelined_5x5` | streaming, float 5×5 | 4096 px | 2.80 ms | 5.72e-06 | PASS |
| 05 | `05_generalized_multichannel` | runtime-configurable kernel, Cin=3→Cout=2, float | 84×128 RGB | 127.14 ms | visual match | PASS |

(05 is slower because the kernel size and channel counts are runtime parameters
rather than compile-time constants — see Report 2 for the tradeoff discussion.)

### How each design-point folder is organized

The five folders don't have identical contents, but the same pieces recur. When
looking for something in a given `design_points/NN_*/`, look for:

- **`conv2d_lab*.ipynb` / `.py`** — the PYNQ deployment notebook. Loads the
  bitstream, streams the test image (`dog.jpg`) through hardware via DMA, times it
  with the AXI timer, and checks the hardware output against a NumPy/SciPy reference.
- **`*.pdf`** (e.g. `conv2d_lab - Jupyter Notebook.pdf`) — a rendered export of that
  notebook's last run, for reading the result without needing a PYNQ board.
- **The HLS project** (`pj1/`, `2D_Conv_Float_5x5/`, or `generalized_conv/` —
  name varies by folder) — open in Vitis HLS. Synthesis reports are at
  `<project>/solution1/syn/report/csynth.rpt`.
- **The exported IP** (`IP/` or `conv2d_stream/`) — the packaged HLS core
  (`component.xml` + `hdl/` + `drivers/`) that gets pulled into the Vivado block design.
- **`UPLOAD FILES/` or `UPLOAD_FILES/`** — the exact bundle to copy onto the PYNQ
  board: bitstream (`.bit`), hardware handoff (`.hwh`), the notebook, and `dog.jpg`.
- **`VIVADO_FILES/` or `project_1_*.xpr`** — the full Vivado project (block design,
  synthesis/implementation runs, bitstream build). Only kept in full for **02, 04,
  and 05**; 01 and 03 reuse 02's block design with just the HLS IP swapped in, so
  only their bitstream + `.hwh` are kept, not the intermediate Vivado project.

> **Note on 04:** `04_float_pipelined_5x5/pj1/` is a leftover copy of the 3×3
> baseline HLS project (top function `conv2d_optimized`, not `conv2d_stream`) —
> it isn't part of this design point. The actual 5×5 HLS project is
> `04_float_pipelined_5x5/2D_Conv_Float_5x5/`.

---

## `synthesis_reports/`

An isolated, apples-to-apples HLS comparison (no PYNQ deployment noise), used for
the datatype and kernel-size tradeoff tables in Report 2:

- **`float/`** — 3×3, floating point
- **`fixed/`** — 3×3, `ap_fixed`, same architecture as `float/`
- **`fixed_128trippoints/`** — fixed-point, sized for a full 128×128 image

Each has `hls_codes/` (the exact source snapshot synthesized) and a `report/` (or
`reports/`) folder with `csynth.rpt` and per-loop breakdowns.

---

## Reproducing a design point end-to-end

1. **HLS (Vitis HLS 2021.1):** open the project folder for that design point
   (`pj1/`, `2D_Conv_Float_5x5/`, or `generalized_conv/`), run C simulation, then
   C synthesis. Reports land in `solution1/syn/report/csynth.rpt`. Export RTL to
   regenerate the IP under `IP/` (or the equivalent named folder).
2. **Vivado:** open the `.xpr` (in `VIVADO_FILES/` or at the top level for 04/05),
   regenerate the block design if prompted, run synthesis → implementation →
   generate bitstream. Output is `design_1_wrapper.bit` + the `.hwh` handoff file.
3. **PYNQ:** copy everything from that design point's `UPLOAD FILES/` (or
   `UPLOAD_FILES/`) folder onto the board, open the notebook in Jupyter, run all
   cells. It streams `dog.jpg` through the accelerator via DMA, times it, and
   compares the hardware output against the software reference.
