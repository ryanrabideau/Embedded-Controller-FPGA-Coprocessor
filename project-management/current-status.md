# Current Status

## Summary

All major engineering deliverables for the Embedded Controller with FPGA Co-Processor have been finished. The repository now reflects a completed portfolio project rather than an in-progress design.

## Completed Work

- System architecture and hardware/software partitioning defined
- Component selection finalized (STM32F401, iCE40UP5K, microSD connector, regulators)
- Full schematic capture in OrCAD (Power, MCU, FPGA, MicroSD pages)
- 4-layer PCB stackup defined and constrained
- 50 Ω microstrip impedance calculated and applied
- Component placement and routing completed
- Series termination and return-path considerations implemented
- PSpice power-rail analysis performed
- Bare-metal STM32 firmware foundation (clock, timer, UART, GPIO)
- Register-level SDIO initialization sequence
- MCU ↔ FPGA 4-bit interface driver
- FPGA Parallel Data Capture Engine written in Verilog
- FPGA testbench + simulation waveforms (Icarus Verilog / GTKWave)
- Top-level repository documentation updated to completed status

## Known Limitations

- Strict ±10 mil length matching was not fully enforced (acceptable for the interface speeds used)
- Live UART output on the development Nucleo board became unreliable (hardware/ST-Link VCP issue); code remains correct
- Board was not fabricated (design-only project)

## Next Actions (Optional)

- Physical fabrication and bring-up (future work)
- Expanded documentation assets (block diagrams, additional screenshots)
- Further SDIO read/write testing if a card and reliable serial console are available
