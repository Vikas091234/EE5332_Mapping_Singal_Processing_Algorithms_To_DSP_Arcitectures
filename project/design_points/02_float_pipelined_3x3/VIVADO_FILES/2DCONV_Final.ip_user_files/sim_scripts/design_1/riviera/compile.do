vlib work
vlib riviera

vlib riviera/xilinx_vip
vlib riviera/xpm
vlib riviera/xbip_utils_v3_0_10
vlib riviera/axi_utils_v2_0_6
vlib riviera/xbip_pipe_v3_0_6
vlib riviera/xbip_dsp48_wrapper_v3_0_4
vlib riviera/xbip_dsp48_addsub_v3_0_6
vlib riviera/xbip_dsp48_multadd_v3_0_6
vlib riviera/xbip_bram18k_v3_0_6
vlib riviera/mult_gen_v12_0_17
vlib riviera/floating_point_v7_1_12
vlib riviera/xil_defaultlib
vlib riviera/axi_infrastructure_v1_1_0
vlib riviera/axi_vip_v1_1_10
vlib riviera/processing_system7_vip_v1_0_12
vlib riviera/lib_pkg_v1_0_2
vlib riviera/fifo_generator_v13_2_5
vlib riviera/lib_fifo_v1_0_14
vlib riviera/lib_srl_fifo_v1_0_2
vlib riviera/lib_cdc_v1_0_2
vlib riviera/axi_datamover_v5_1_26
vlib riviera/axi_sg_v4_1_13
vlib riviera/axi_dma_v7_1_25
vlib riviera/axi_lite_ipif_v3_0_4
vlib riviera/axi_timer_v2_0_26
vlib riviera/generic_baseblocks_v2_1_0
vlib riviera/axi_register_slice_v2_1_24
vlib riviera/axi_data_fifo_v2_1_23
vlib riviera/axi_crossbar_v2_1_25
vlib riviera/axi_protocol_converter_v2_1_24
vlib riviera/proc_sys_reset_v5_0_13
vlib riviera/axi_clock_converter_v2_1_23
vlib riviera/blk_mem_gen_v8_4_4
vlib riviera/axi_dwidth_converter_v2_1_24

vmap xilinx_vip riviera/xilinx_vip
vmap xpm riviera/xpm
vmap xbip_utils_v3_0_10 riviera/xbip_utils_v3_0_10
vmap axi_utils_v2_0_6 riviera/axi_utils_v2_0_6
vmap xbip_pipe_v3_0_6 riviera/xbip_pipe_v3_0_6
vmap xbip_dsp48_wrapper_v3_0_4 riviera/xbip_dsp48_wrapper_v3_0_4
vmap xbip_dsp48_addsub_v3_0_6 riviera/xbip_dsp48_addsub_v3_0_6
vmap xbip_dsp48_multadd_v3_0_6 riviera/xbip_dsp48_multadd_v3_0_6
vmap xbip_bram18k_v3_0_6 riviera/xbip_bram18k_v3_0_6
vmap mult_gen_v12_0_17 riviera/mult_gen_v12_0_17
vmap floating_point_v7_1_12 riviera/floating_point_v7_1_12
vmap xil_defaultlib riviera/xil_defaultlib
vmap axi_infrastructure_v1_1_0 riviera/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_10 riviera/axi_vip_v1_1_10
vmap processing_system7_vip_v1_0_12 riviera/processing_system7_vip_v1_0_12
vmap lib_pkg_v1_0_2 riviera/lib_pkg_v1_0_2
vmap fifo_generator_v13_2_5 riviera/fifo_generator_v13_2_5
vmap lib_fifo_v1_0_14 riviera/lib_fifo_v1_0_14
vmap lib_srl_fifo_v1_0_2 riviera/lib_srl_fifo_v1_0_2
vmap lib_cdc_v1_0_2 riviera/lib_cdc_v1_0_2
vmap axi_datamover_v5_1_26 riviera/axi_datamover_v5_1_26
vmap axi_sg_v4_1_13 riviera/axi_sg_v4_1_13
vmap axi_dma_v7_1_25 riviera/axi_dma_v7_1_25
vmap axi_lite_ipif_v3_0_4 riviera/axi_lite_ipif_v3_0_4
vmap axi_timer_v2_0_26 riviera/axi_timer_v2_0_26
vmap generic_baseblocks_v2_1_0 riviera/generic_baseblocks_v2_1_0
vmap axi_register_slice_v2_1_24 riviera/axi_register_slice_v2_1_24
vmap axi_data_fifo_v2_1_23 riviera/axi_data_fifo_v2_1_23
vmap axi_crossbar_v2_1_25 riviera/axi_crossbar_v2_1_25
vmap axi_protocol_converter_v2_1_24 riviera/axi_protocol_converter_v2_1_24
vmap proc_sys_reset_v5_0_13 riviera/proc_sys_reset_v5_0_13
vmap axi_clock_converter_v2_1_23 riviera/axi_clock_converter_v2_1_23
vmap blk_mem_gen_v8_4_4 riviera/blk_mem_gen_v8_4_4
vmap axi_dwidth_converter_v2_1_24 riviera/axi_dwidth_converter_v2_1_24

vlog -work xilinx_vip  -sv2k12 "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
"/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
"/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"/opt/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"/opt/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"/opt/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"/opt/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work xbip_utils_v3_0_10 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/b417/hdl/xbip_utils_v3_0_vh_rfs.vhd" \

vcom -work axi_utils_v2_0_6 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/1971/hdl/axi_utils_v2_0_vh_rfs.vhd" \

vcom -work xbip_pipe_v3_0_6 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/7468/hdl/xbip_pipe_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_wrapper_v3_0_4 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/cdbf/hdl/xbip_dsp48_wrapper_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_addsub_v3_0_6 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/910d/hdl/xbip_dsp48_addsub_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_multadd_v3_0_6 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/b0ac/hdl/xbip_dsp48_multadd_v3_0_vh_rfs.vhd" \

vcom -work xbip_bram18k_v3_0_6 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/d367/hdl/xbip_bram18k_v3_0_vh_rfs.vhd" \

vcom -work mult_gen_v12_0_17 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/dd36/hdl/mult_gen_v12_0_vh_rfs.vhd" \

vcom -work floating_point_v7_1_12 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/bf60/hdl/floating_point_v7_1_rfs.vhd" \

vlog -work floating_point_v7_1_12  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/bf60/hdl/floating_point_v7_1_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_conv2d_stream_Pipeline_VITIS_LOOP_33_1.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_conv2d_stream_Pipeline_VITIS_LOOP_47_2.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_conv2d_stream_Pipeline_VITIS_LOOP_52_3_VITIS_LOOP_53_4.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_conv2d_stream_Pipeline_VITIS_LOOP_66_5_VITIS_LOOP_67_6.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_CTRL_s_axi.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_fadd_32ns_32ns_32_4_full_dsp_1.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_flow_control_loop_pipe_sequential_init.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_fmul_32ns_32ns_32_2_max_dsp_1.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_hls_deadlock_idx0_monitor.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_hls_deadlock_idx1_monitor.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_line_buf_0.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_mul_32ns_32ns_64_1_1.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_mul_32s_32s_32_1_1.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream_regslice_both.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog/conv2d_stream.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/ip/conv2d_stream_fmul_32ns_32ns_32_2_max_dsp_1_ip.v" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/ip/conv2d_stream_fadd_32ns_32ns_32_4_full_dsp_1_ip.v" \
"../../../bd/design_1/ip/design_1_conv2d_stream_0_0/sim/design_1_conv2d_stream_0_0.v" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_10  -sv2k12 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/0980/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_12  -sv2k12 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0/sim/design_1_processing_system7_0_0.v" \

vcom -work lib_pkg_v1_0_2 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vlog -work fifo_generator_v13_2_5  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/276e/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_5 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/276e/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_5  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/276e/hdl/fifo_generator_v13_2_rfs.v" \

vcom -work lib_fifo_v1_0_14 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/a5cb/hdl/lib_fifo_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_2 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work axi_datamover_v5_1_26 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/1e21/hdl/axi_datamover_v5_1_vh_rfs.vhd" \

vcom -work axi_sg_v4_1_13 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/4919/hdl/axi_sg_v4_1_rfs.vhd" \

vcom -work axi_dma_v7_1_25 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/1faa/hdl/axi_dma_v7_1_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/design_1/ip/design_1_axi_dma_0_0/sim/design_1_axi_dma_0_0.vhd" \

vcom -work axi_lite_ipif_v3_0_4 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work axi_timer_v2_0_26 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ae8a/hdl/axi_timer_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/design_1/ip/design_1_axi_timer_0_0/sim/design_1_axi_timer_0_0.vhd" \

vlog -work generic_baseblocks_v2_1_0  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_24  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/8f68/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work axi_data_fifo_v2_1_23  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/94ec/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_25  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/3917/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xbar_0/sim/design_1_xbar_0.v" \

vlog -work axi_protocol_converter_v2_1_24  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/6e0d/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_pc_0/sim/design_1_auto_pc_0.v" \

vcom -work proc_sys_reset_v5_0_13 -93 \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/design_1/ip/design_1_rst_ps7_0_50M_0/sim/design_1_rst_ps7_0_50M_0.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xbar_1/sim/design_1_xbar_1.v" \

vlog -work axi_clock_converter_v2_1_23  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/7ee4/hdl/axi_clock_converter_v2_1_vl_rfs.v" \

vlog -work blk_mem_gen_v8_4_4  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/2985/simulation/blk_mem_gen_v8_4.v" \

vlog -work axi_dwidth_converter_v2_1_24  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/3d13/hdl/axi_dwidth_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ef07/hdl/verilog" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+../../../../2DCONV_Final.gen/sources_1/bd/design_1/ip/design_1_conv2d_stream_0_0/drivers/conv2d_stream_v1_0/src" "+incdir+/opt/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_us_0/sim/design_1_auto_us_0.v" \
"../../../bd/design_1/ip/design_1_auto_us_1/sim/design_1_auto_us_1.v" \
"../../../bd/design_1/ip/design_1_auto_pc_1/sim/design_1_auto_pc_1.v" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work xil_defaultlib \
"glbl.v"

