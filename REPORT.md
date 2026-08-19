# EE5332 Coursework and Project Report

## 1. Overview

This repository contains selected coursework from **EE5332 — Mapping Signal Processing Algorithms to DSP Architectures** at IIT Madras and the associated 2D convolution accelerator project.

The work progresses from RTL and C-based DSP implementations to Vitis HLS optimization, AXI interfaces, FPGA integration, and PYNQ-based hardware validation.

The repository contains two main parts:

1. **Labs 1–5** — individual coursework exercises.
2. **Course project** — a streaming K×K 2D convolution accelerator explored through five design points.

---

# 2. Laboratory Work

## 2.1 Lab 1 — RTL and SystemVerilog

Lab 1 consists of four RTL exercises:

- counter
- extend-and-negate
- sequence detector
- shift register

Each exercise includes a design module and a corresponding SystemVerilog test bench.

The laboratory material also includes `dsdlabs-main`, which contains additional FPGA-oriented examples:

- counter implementation
- FPGA counter
- pin constraints
- multiplier/timing example

The supplied lab instructions specify simulation using Icarus Verilog.

### Main learning focus

- synthesizable RTL
- module/testbench structure
- synchronous digital logic
- simulation-based verification
- basic FPGA-oriented design

---

## 2.2 Lab 2 — FIR Filter in C

Lab 2 implements a FIR filtering kernel in C.

The test flow uses Python to generate:

- FIR coefficients
- input test data
- expected reference output

The C test bench then compares the FIR implementation against the generated reference.

The supplied lab documentation describes a **51-tap low-pass FIR** using a windowed-sinc/Hamming coefficient-generation method.

### Main learning focus

- FIR filter implementation
- C-based DSP kernels
- software reference generation
- automated test-vector verification

---

## 2.3 Lab 3 — Vitis HLS Optimization

Lab 3 applies Vitis HLS directives to a differential-equation solver.

The submitted material contains four directive sets and four corresponding synthesis reports.

The experiments investigate the effect of:

- default synthesis,
- pipelining constraints,
- multiplier-resource limits,
- initiation interval,
- timing constraints.

The lab report and screenshots document the resulting synthesis experiments.

### Main learning focus

- C/C++ to RTL synthesis
- HLS directives
- initiation interval
- resource constraints
- synthesis-report interpretation

---

## 2.4 Lab 4 — FIR HLS Synthesis

Lab 4 synthesizes the FIR filter using Vitis HLS.

The supplied assignment requires exploration of:

1. default synthesis,
2. directive-based optimization targeting II = 1 and improved frequency,
3. a maximum multiplier constraint.

The design also uses AXI-Stream interfaces for the FIR input/output.

The repository contains the FIR source and testbench, coefficient/test-vector data, four directive/report sets, screenshots, and the submitted analysis PDF.

### Main learning focus

- FIR hardware synthesis
- pipeline optimization
- resource constraints
- AXI-Stream interfaces
- synthesis tradeoffs

---

## 2.5 Lab 5 — Streaming FIR on PYNQ

Lab 5 extends the FIR implementation to FPGA hardware and compares two interfaces:

### MMIO / AXI-Lite

The processor communicates with the FIR IP one sample at a time.

### DMA / AXI-Stream

The processor transfers a block of samples through DMA while the FIR accelerator processes the stream.

The repository contains:

- HLS streaming FIR
- HLS MMIO FIR
- test benches
- synthesis scripts
- Vivado block-design creation script
- PYNQ notebook and Python script
- generated bitstream and hardware handoff
- input/reference data

The lab also provides experiments involving unrolling, pipelining, resource usage, fixed-point representation, and timing.

### Main learning focus

- hardware/software co-design
- AXI-Lite versus AXI-Stream
- DMA-based acceleration
- PYNQ deployment
- FPGA performance measurement

---

# 3. Course Project — 2D Convolution Accelerator

## 3.1 Objective

The course project implements a **K×K convolution accelerator**, with K = 3 or 5 depending on the design point, for grayscale/RGB image data.

The accelerator processes image data as a stream and uses a line-buffer/sliding-window architecture suitable for FPGA implementation.

The project is organized around the following flow:

```text
Software reference
       │
       ▼
HLS C/C++ implementation
       │
       ▼
Vitis HLS synthesis
       │
       ▼
Exported accelerator IP
       │
       ▼
Vivado integration
       │
       ▼
AXI/DMA + Zynq processing system
       │
       ▼
PYNQ hardware execution
       │
       ▼
Comparison with NumPy/SciPy reference
```

---

# 4. Convolution Architecture

The core architecture uses a **line buffer** and **sliding window**.

For a K×K convolution, previously received image rows are retained in line buffers. As new pixels arrive, the buffers and window shift so that the accelerator can construct the K×K neighborhood required for the current output.

This avoids repeatedly reading the same pixels from external memory.

The architecture therefore emphasizes:

- spatial data reuse,
- streaming input,
- local buffering,
- pipelined computation,
- parallel multiply-accumulate operations.

The project reports and HTML stepper visualizations provide additional documentation of this mechanism.

---

# 5. Design-Space Exploration

Five design points are present.

| # | Design point | Main configuration | Purpose |
|---|---|---|---|
| 01 | `01_baseline_no_pragma` | Float 3×3 streaming baseline | Baseline implementation |
| 02 | `02_float_pipelined_3x3` | Float 3×3 with pipelining/unrolling | Improve throughput |
| 03 | `03_fixed_pipelined_3x3` | Fixed-point 3×3, `ap_fixed<16,3>` | Study precision/resource tradeoff |
| 04 | `04_float_pipelined_5x5` | Float 5×5 | Study larger convolution kernel |
| 05 | `05_generalized_multichannel` | Runtime-configurable multichannel | Study generality and channel support |

These folders contain different combinations of HLS projects, exported IP, PYNQ deployment material, Vivado projects, reports, and supporting files. They should therefore **not** be represented as five identical directory templates.

---

# 6. Design Point 01 — Baseline 3×3

`01_baseline_no_pragma/` contains the baseline streaming 3×3 implementation.

Important material includes:

- convolution source/header files
- HLS project
- synthesis report
- PYNQ notebook/script
- PYNQ bitstream and `.hwh`
- test image
- supporting screenshot/PDF

The baseline provides the reference hardware architecture against which the optimized implementations can be compared.

---

# 7. Design Point 02 — Floating-Point Pipelined 3×3

`02_float_pipelined_3x3/` contains the optimized floating-point 3×3 implementation.

The directory includes:

- HLS source and testbench
- HLS project
- exported accelerator IP
- Vivado project material
- PYNQ notebook/script
- bitstream and `.hwh`
- synthesis report
- notebook PDF export

The main optimization direction is increased parallelism through **pipelining and loop unrolling**.

---

# 8. Design Point 03 — Fixed-Point Pipelined 3×3

`03_fixed_pipelined_3x3/` evaluates a fixed-point implementation of the 3×3 accelerator.

The project uses:

```text
ap_fixed<16,3>
```

for the principal fixed-point datapath described in the project material.

This design point allows the effect of reduced numerical precision to be compared with the floating-point implementation in terms of:

- output accuracy,
- resource requirements,
- timing,
- hardware suitability.

The directory contains fixed-point source/notebook material, HLS data, exported hardware files, and the associated synthesis report.

---

# 9. Design Point 04 — Floating-Point 5×5

`04_float_pipelined_5x5/` extends the convolution kernel from 3×3 to 5×5.

The directory contains a dedicated HLS project named:

```text
2D_Conv_Float_5x5/
```

as well as PYNQ deployment material and Vivado-related generated files.

This design point is useful for examining the cost and behavior of a larger convolution window.

> The directory also contains a `pj1/` HLS project that the project documentation identifies as a leftover copy of the 3×3 baseline project. It should not be interpreted as the actual 5×5 HLS implementation.

---

# 10. Design Point 05 — Generalized Multichannel

`05_generalized_multichannel/` contains the generalized convolution implementation.

The project material describes this design as runtime-configurable and capable of multichannel operation. The documented hardware experiment uses:

```text
Cin = 3
Cout = 2
```

with floating-point computation.

The directory includes:

- generalized HLS project
- exported convolution IP
- Vivado project
- PYNQ deployment files
- multichannel notebook/PDF
- hardware bitstream and `.hwh`

This design emphasizes generality rather than only maximizing the throughput of a fixed compile-time 3×3 implementation.

---

# 11. Synthesis Reports

The repository contains a separate:

```text
project/synthesis_reports/
```

directory for isolated HLS comparisons.

It contains:

```text
synthesis_reports/
├── float/
├── fixed/
└── fixed_128trippoints/
```

These datasets are intended for examining the effects of datatype and configuration changes without treating the complete PYNQ/Vivado deployment directories as the comparison itself.

The `float/` and `fixed/` material contains source snapshots and HLS reports. The `fixed_128trippoints/` material contains a fixed-point configuration associated with a 128×128 image size.

---

# 12. Verification and Hardware Validation

The project uses multiple levels of verification.

## Software verification

C/C++ implementations are compared against software reference calculations.

## HLS verification

Vitis HLS provides C simulation and synthesis reports for the accelerator implementations.

## FPGA integration

The exported HLS IP is integrated into Vivado designs using the appropriate AXI/DMA infrastructure.

## PYNQ validation

The deployment notebooks/scripts:

1. load the generated hardware,
2. load the input image,
3. transfer image data through the accelerator,
4. measure execution time,
5. compare hardware output with a NumPy/SciPy reference.

This creates a complete software-to-hardware validation flow rather than relying only on HLS estimates.

---

# 13. Project Documentation

The `project/report/` directory contains:

### `EE19B108_Report1_Sliding_Window`

A supplementary walkthrough of the line-buffer/sliding-window implementation.

### `EE19B108_Report2_Project_Report`

The main project report containing the design exploration, tradeoff analysis, and hardware validation results.

### HTML stepper visualizations

Interactive visualizations are included for understanding the movement of the line buffer and sliding window.

---

# 14. Technical Skills Demonstrated

## Digital design

- SystemVerilog RTL
- testbench development
- synchronous digital logic
- FPGA-oriented design

## DSP

- FIR filters
- 2D convolution
- software reference models
- coefficient/test-vector generation

## HLS

- C/C++ hardware description
- pipelining
- loop unrolling
- initiation-interval optimization
- resource constraints
- fixed-point arithmetic

## FPGA systems

- Vivado
- Vitis HLS
- AXI-Stream
- AXI-Lite
- DMA
- PYNQ/Zynq

## Hardware/software co-design

- software reference versus hardware implementation
- IP generation
- processor/accelerator integration
- hardware validation
- performance/resource/precision tradeoff analysis

---

# 15. Repository Accuracy Notes

The repository contains a mixture of:

- source code,
- test benches,
- reports,
- notebooks,
- generated synthesis results,
- exported IP,
- Vivado project data,
- FPGA bitstreams,
- hardware handoff files,
- logs and caches.

Consequently, a completely exhaustive tree would be dominated by generated tool files and would obscure the actual coursework.

The README therefore uses a **representative but verified tree** for the major source/documentation structure. It does not claim that every generated file is shown.

In particular:

- there is **no `requirements.txt`** in the supplied top-level coursework structure;
- `labs/lab1/` contains both the submitted-style `lab1/` material and the separate `dsdlabs-main/` material;
- Labs 3 and 4 contain four directive/report sets in the supplied files;
- Lab 5 contains both MMIO and streaming HLS implementations;
- the project has exactly **five named design-point directories**;
- the project also contains separate `src/`, `report/`, and `synthesis_reports/` directories;
- the five design-point folders are not structurally identical;
- generated HLS/Vivado directories are intentionally abbreviated in the documentation tree.

This representation is based on the supplied `labs(1).zip`, `project(2).zip`, existing README, existing report, and `.gitignore`, rather than assuming a generic EE5332 repository layout.
