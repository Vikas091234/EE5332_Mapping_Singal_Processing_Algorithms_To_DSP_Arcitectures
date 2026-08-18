# Makefile for Lab 5 FIR filter -- simulation, synthesis, and IP export
#
# Simulation uses the system compiler with Vitis HLS headers.
# Synthesis and export use vitis_hls in batch mode (no csim).
#
# Required environment:
#   XILINX_HLS    -- path to Vitis HLS installation
#                    (e.g. /opt/Xilinx/Vitis_HLS/2021.1)
#   XILINX_VIVADO -- path to Vivado installation
#                    (e.g. /opt/Xilinx/Vivado/2021.1)
#
# Targets:
#   make sim_mmio      -- compile and run MMIO testbench
#   make sim_stream    -- compile and run streaming testbench
#   make sim           -- run both simulations
#   make synth_mmio    -- HLS synthesis + IP export for MMIO
#   make synth_stream  -- HLS synthesis + IP export for streaming
#   make synth         -- synthesise both IPs
#   make all           -- simulate + synthesise everything
#   make clean         -- remove build products

# ---- toolchain ----
CXX      := g++
CXXFLAGS := -std=c++14 -g -O0 -Wall -Wno-unknown-pragmas -Wno-int-in-bool-context
XILINX_HLS ?= /opt/Xilinx/Vitis_HLS/2021.1
HLS_INC  := -I$(XILINX_HLS)/include

PART     := xc7z020clg400-1
CLOCK_NS := 10

# ---- file lists ----
COMMON_H   := fir_common.h fir_coeffs.h

MMIO_SRC   := fir_mmio.cpp
MMIO_TB    := fir_mmio_tb.cpp
MMIO_HDR   := fir_mmio.h $(COMMON_H)

STREAM_SRC := fir_stream.cpp
STREAM_TB  := fir_stream_tb.cpp
STREAM_HDR := fir_stream.h $(COMMON_H)

VECTORS    := ../input.txt ../expected_output.txt

# ---- default target ----
all: sim synth

# ==================================================================
# Simulation -- system compiler, Vitis HLS headers only
# ==================================================================
sim: sim_mmio sim_stream

sim_mmio: csim_mmio $(VECTORS)
	@echo "---- MMIO C simulation ----"
	./csim_mmio

sim_stream: csim_stream $(VECTORS)
	@echo "---- Streaming C simulation ----"
	./csim_stream

csim_mmio: $(MMIO_SRC) $(MMIO_TB) $(MMIO_HDR)
	$(CXX) $(CXXFLAGS) $(HLS_INC) -o $@ $(MMIO_SRC) $(MMIO_TB)

csim_stream: $(STREAM_SRC) $(STREAM_TB) $(STREAM_HDR)
	$(CXX) $(CXXFLAGS) $(HLS_INC) -o $@ $(STREAM_SRC) $(STREAM_TB)

$(VECTORS): ../generate_vectors.py
	cd .. && python3 generate_vectors.py

# ==================================================================
# Synthesis + IP export -- vitis_hls in batch mode (skip csim)
# ==================================================================
synth: synth_mmio synth_stream

synth_mmio: $(MMIO_SRC) $(MMIO_HDR)
	vitis_hls -f synth_mmio.tcl

synth_stream: $(STREAM_SRC) $(STREAM_HDR)
	vitis_hls -f synth_stream.tcl

# ==================================================================
# Clean
# ==================================================================
clean:
	rm -f csim_mmio csim_stream
	rm -rf hls_fir_mmio hls_fir_stream
	rm -f vitis_hls.log

.PHONY: all sim sim_mmio sim_stream synth synth_mmio synth_stream clean
