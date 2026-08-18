# EE5332 Coursework Report

## Overview

This repository contains selected EE5332 coursework and the course project on mapping signal-processing algorithms to FPGA/DSP architectures.

## Labs

### Lab 1 — RTL and FPGA basics
Implemented and verified basic RTL blocks including counters, shift registers, sequence detection, and arithmetic/sign-extension logic. The included `dsdlabs-main` material also contains FPGA-oriented counter, multiplier, pin-constraint, and synthesis examples.

### Lab 2 — FIR filter in C
Implemented a FIR filtering kernel in C and verified it against Python-generated reference vectors. The flow demonstrates coefficient generation, test-vector generation, C compilation, and automated comparison.

### Lab 3 — Vitis HLS optimization
Explored how synthesis directives affect a differential-equation solver. Multiple solutions were synthesized with different pipelining, multiplier-resource, initiation-interval, and timing constraints.

### Lab 4 — FIR filter synthesis
Explored HLS implementations of a FIR filter using multiple directive configurations, including initiation-interval optimization, multiplier constraints, and AXI-Stream interfaces.

### Lab 5 — Streaming FIR on PYNQ
Compared CPU/MMIO-style processing with a DMA/AXI-Stream hardware implementation. The flow includes HLS source, Vivado integration, PYNQ execution, test vectors, and synthesis reports.

## Course Project

### 2D Convolution Accelerator on FPGA

The main project maps 2D convolution onto an FPGA-oriented streaming architecture.

The implementation uses:

- Line-buffer based data reuse
- Sliding-window convolution
- Compile-time and runtime kernel configurations
- Loop pipelining
- Loop unrolling
- Floating-point and fixed-point arithmetic
- AXI-Stream interfaces
- PYNQ hardware validation

Five design points were explored to study the tradeoff between throughput, resource usage, precision, and generality.

The repository retains the source implementations and selected synthesis reports so that the design decisions can be inspected without committing the large generated HLS/Vivado build trees.

## Skills demonstrated

- Digital design and RTL
- DSP algorithm implementation
- Hardware/software co-design
- HLS optimization
- FPGA architecture
- Pipelining and parallelism
- Fixed-point arithmetic
- Streaming architectures
- Hardware verification
- Performance/resource tradeoff analysis
