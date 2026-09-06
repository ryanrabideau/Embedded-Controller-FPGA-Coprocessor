# Current Status

## Summary

All major engineering deliverables for the Embedded Controller with FPGA Co-Processor have been completed. The repository represents a completed design and verification portfolio project.

## Completed Work

- System architecture and hardware/software partitioning defined
- Component selection finalized (STM32F401, iCE40UP5K, microSD connector, regulators)
- Full schematic capture completed in OrCAD (Power, MCU, FPGA, and MicroSD pages)
- 4-layer PCB stackup defined and constrained
- 50 Ω single-ended microstrip routing target calculated and applied
- Component placement and routing completed with 0 unrouted connections and 0 DRC errors
- Series termination and return-path considerations implemented
- Simplified 3.3 V power-rail load-step analysis performed in PSpice
- Bare-metal STM32 firmware foundation implemented (clock, timer, UART, GPIO)
- UART output verified successfully at 115200 baud after correcting the USART2 baud-rate configuration for the 42 MHz APB1 clock
- Register-level SDIO initialization sequence implemented
- MCU-to-FPGA synchronous 4-bit interface implemented in firmware
- FPGA Parallel Data Capture Engine implemented in Verilog
- FPGA functionality verified using a self-checking Icarus Verilog testbench and GTKWave simulation
- Hardware, firmware, FPGA, simulation, and architecture documentation added to the repository

## Known Limitations

- The PCB was not fabricated, so the complete system has not undergone physical board-level bring-up or end-to-end hardware validation
- SDIO initialization firmware was implemented but has not been validated with the target microSD hardware
- The MCU-to-FPGA interface was implemented in firmware and RTL but has not been physically validated between the target devices
- Strict ±10 mil length matching was not fully enforced; routing was considered sufficient for the intended interface speeds

## Future Work

- Fabricate and assemble the PCB
- Perform board bring-up and power-rail measurements
- Validate MCU-to-FPGA communication on physical hardware
- Validate microSD initialization and implement block-level read/write functionality
- Expand FPGA functionality beyond the current parallel capture proof of concept
