# Embedded Controller with FPGA Co-Processor

> **Status:** In Development

A 4-layer embedded controller integrating an STM32F401 microcontroller, Lattice iCE40 FPGA co-processor, and microSD SDIO interface. The project combines PCB design, bare-metal embedded firmware, FPGA RTL development, and signal/power integrity analysis.

## Project Overview

This system is being developed as an FPGA-assisted embedded data acquisition platform. The FPGA provides deterministic, timing-critical data capture and buffering, while the STM32 handles higher-level system control, communication, and data storage.

### Planned Engineering Features

- STM32F401 microcontroller
- Lattice iCE40 FPGA co-processor
- 4-layer PCB
- MicroSD storage using 4-bit SDIO
- Multi-rail FPGA power architecture
- Controlled-impedance routing
- Source termination and length matching
- Signal integrity and return-path considerations
- PSpice power integrity analysis
- Register-level STM32 firmware
- SystemVerilog RTL
- RTL simulation and verification

## Current Status

**Active development**

Detailed design files, simulation results, firmware, RTL, and engineering documentation will be added as development progresses.
