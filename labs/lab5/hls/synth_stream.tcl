# synth_stream.tcl -- HLS synthesis + IP export for streaming FIR
#
# Usage:  vitis_hls -f synth_stream.tcl
#         (or: make synth_stream)

set PART     "xc7z020clg400-1"
set CLOCK_NS "10"
set TOP      "fir_stream"
set PROJ     "hls_fir_stream"

open_project ${PROJ} -reset
set_top ${TOP}
add_files fir_stream.cpp

open_solution "sol1" -flow_target vivado -reset
set_part ${PART}
create_clock -period ${CLOCK_NS} -name default

csynth_design

export_design -format ip_catalog \
    -description "Streaming FIR filter (${TOP})" \
    -vendor "ee5332" -library "hls" -version "1.0"

exit
