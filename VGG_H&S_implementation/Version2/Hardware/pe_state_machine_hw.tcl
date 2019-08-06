# TCL File Generated by Component Editor 18.1
# Wed Jul 31 15:07:10 EDT 2019
# DO NOT MODIFY


# 
# pe_state_machine "pe_state_machine" v1.5
#  2019.07.31.15:07:10
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module pe_state_machine
# 
set_module_property DESCRIPTION ""
set_module_property NAME pe_state_machine
set_module_property VERSION 1.5
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME pe_state_machine
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL pe_state_machine
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file pe_state_machine.sv SYSTEM_VERILOG PATH pe_state_machine.sv TOP_LEVEL_FILE


# 
# parameters
# 


# 
# display items
# 


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock CMSIS_SVD_VARIABLES ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clk clk Input 1


# 
# connection point avalon_slave_0
# 
add_interface avalon_slave_0 avalon end
set_interface_property avalon_slave_0 addressUnits WORDS
set_interface_property avalon_slave_0 associatedClock clock
set_interface_property avalon_slave_0 associatedReset reset
set_interface_property avalon_slave_0 bitsPerSymbol 8
set_interface_property avalon_slave_0 burstOnBurstBoundariesOnly false
set_interface_property avalon_slave_0 burstcountUnits WORDS
set_interface_property avalon_slave_0 explicitAddressSpan 0
set_interface_property avalon_slave_0 holdTime 0
set_interface_property avalon_slave_0 linewrapBursts false
set_interface_property avalon_slave_0 maximumPendingReadTransactions 0
set_interface_property avalon_slave_0 maximumPendingWriteTransactions 0
set_interface_property avalon_slave_0 readLatency 0
set_interface_property avalon_slave_0 readWaitTime 1
set_interface_property avalon_slave_0 setupTime 0
set_interface_property avalon_slave_0 timingUnits Cycles
set_interface_property avalon_slave_0 writeWaitTime 0
set_interface_property avalon_slave_0 ENABLED true
set_interface_property avalon_slave_0 EXPORT_OF ""
set_interface_property avalon_slave_0 PORT_NAME_MAP ""
set_interface_property avalon_slave_0 CMSIS_SVD_VARIABLES ""
set_interface_property avalon_slave_0 SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave_0 write write Input 1
add_interface_port avalon_slave_0 chipselect chipselect Input 1
add_interface_port avalon_slave_0 writedata writedata Input 32
add_interface_port avalon_slave_0 readdata readdata Output 32
add_interface_port avalon_slave_0 address address Input 4
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isPrintableDevice 0


# 
# connection point conduit_end
# 
add_interface conduit_end conduit end
set_interface_property conduit_end associatedClock clock
set_interface_property conduit_end associatedReset ""
set_interface_property conduit_end ENABLED true
set_interface_property conduit_end EXPORT_OF ""
set_interface_property conduit_end PORT_NAME_MAP ""
set_interface_property conduit_end CMSIS_SVD_VARIABLES ""
set_interface_property conduit_end SVD_ADDRESS_GROUP ""

add_interface_port conduit_end addr_input_pe addr_input_pe Output 17
add_interface_port conduit_end addr_weight_pe addr_weight_pe Output 17
add_interface_port conduit_end addr_write_pe addr_output_pe Output 15
add_interface_port conduit_end input_master_en input_master_en Output 1
add_interface_port conduit_end weight_master_en weight_master_en Output 1
add_interface_port conduit_end output_master_en output_master_en Output 1
add_interface_port conduit_end rst_n_pe rst_n_pe Output 1
add_interface_port conduit_end conv_num conv_num Output 4
add_interface_port conduit_end relu_en relu_en Output 1
add_interface_port conduit_end pool_en pool_en Output 1
add_interface_port conduit_end output_en output_en Output 1
add_interface_port conduit_end readdatavalid_input readdatavalid_input Input 1
add_interface_port conduit_end readdatavalid_weight readdatavalid_weight Input 1
add_interface_port conduit_end partial_en partial_en Output 1


# 
# connection point conduit_end_buffer
# 
add_interface conduit_end_buffer conduit end
set_interface_property conduit_end_buffer associatedClock clock
set_interface_property conduit_end_buffer associatedReset ""
set_interface_property conduit_end_buffer ENABLED true
set_interface_property conduit_end_buffer EXPORT_OF ""
set_interface_property conduit_end_buffer PORT_NAME_MAP ""
set_interface_property conduit_end_buffer CMSIS_SVD_VARIABLES ""
set_interface_property conduit_end_buffer SVD_ADDRESS_GROUP ""

add_interface_port conduit_end_buffer addr_s2p_buffer write_addr_buffer_out Output 17


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset rst_n reset_n Input 1

