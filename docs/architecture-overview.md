# System Architecture Overview

## Purpose

This project is a 4-layer embedded controller that combines an STM32F401 microcontroller with a Lattice iCE40 FPGA and microSD storage. The design demonstrates practical hardware/software partitioning, controlled-impedance PCB practices, bare-metal firmware, and basic signal and power integrity awareness.

## Hardware Partitioning

**STM32F401 (MCU)**
- System master
- Runs bare-metal firmware
- Handles SDIO communication with the microSD card
- Drives the 4-bit interface to the FPGA
- Manages overall control and higher-level tasks

**Lattice iCE40 (FPGA)**
- Acts as a co-processor
- Implements a Parallel Data Capture Engine
- Captures 4-bit data synchronously with an MCU-supplied clock
- Provides an interrupt back to the MCU when a capture threshold is reached

**microSD**
- Connected via 4-bit SDIO
- Intended for data logging / storage

## Key Interfaces

- MCU to FPGA: synchronous 4-bit bus (CLK, CS, DATA[3:0], IRQ)
- MCU to microSD: 4-bit SDIO
- Debug: UART

## Design Priorities

- Keep high-speed signals short and referenced to a continuous ground plane
- Use controlled 50 Ω routing on the SDIO and MCU to FPGA buses
- Apply series termination near the drivers
- Maintain a clean multi-rail power architecture (3.3 V and 1.2 V)
- Prefer register-level firmware over heavy abstraction
