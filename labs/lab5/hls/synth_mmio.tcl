# synth_mmio.tcl -- HLS synthesis + IP export for MMIO FIR
#
# Usage:  vitis_hls -f synth_mmio.tcl
#         (or: make synth_mmio)

set PART     "xc7z020clg400-1"
set CLOCK_NS "10"
set TOP      "fir_mmio"
set PROJ     "hls_fir_mmio"

open_project ${PROJ} -reset
set_top ${TOP}
add_files fir_mmio.cpp

open_solution "sol1" -flow_target vivado -reset
set_part ${PART}
create_clock -period ${CLOCK_NS} -name default

csynth_design

export_design -format ip_catalog \
    -description "MMIO FIR filter (${TOP})" \
    -vendor "ee5332" -library "hls" -version "1.0"

exit
