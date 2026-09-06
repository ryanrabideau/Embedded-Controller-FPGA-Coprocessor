# Embedded Controller with FPGA Co-Processor

A 4-layer embedded controller integrating an STM32F401 microcontroller, Lattice iCE40 FPGA co-processor, and microSD (4-bit SDIO). The project demonstrates hardware/software partitioning, controlled-impedance PCB design, bare-metal firmware, FPGA RTL, and signal/power integrity analysis.

## Project Overview

This system is an FPGA-assisted data acquisition platform. The FPGA performs deterministic parallel data capture and buffering, while the STM32 handles system control, MCU to FPGA communication, higher-level processing, and microSD storage.

## Key Features

- STM32F401 (LQFP) – bare-metal / register-level firmware
- Lattice iCE40UP5K – Parallel Data Capture Engine (Verilog)
- 4-bit SDIO microSD interface
- 4-layer PCB with controlled-impedance routing
- Multi-rail power (3.3 V + 1.2 V) with PSpice analysis
- Source series termination and return-path aware layout
- MCU to FPGA synchronous 4-bit interface with interrupt

## Repository Structure

- Hardware/ — Schematic, PCB, BOM, stackup
- Firmware/ — STM32 bare-metal project
- FPGA/ — Verilog RTL + testbench + waveforms
- Simulation/ — PSpice power integrity results
- Docs/ — Architecture, SI/PI notes, design decisions
- Project Management/

## Tools Used

- OrCAD Capture / PCB Editor
- OrCAD PSpice
- STM32CubeIDE (register-level)
- Icarus Verilog + GTKWave
- Git / GitHub

## Results Summary

- Complete 4-layer schematic and layout
- 50 Ω microstrip impedance calculated and constrained
- Register-level SDIO initialization sequence
- Working MCU to FPGA 4-bit communication
- FPGA Parallel Capture module simulated with waveforms
- Power-rail transient analysis performed in PSpice

## Skills Covered

- 4-layer PCB design and stackup definition
- Controlled impedance (50 Ω microstrip) calculation and constraint setup
- Signal integrity fundamentals (return path, termination, length matching considerations)
- Multi-rail power architecture and basic power integrity analysis (PSpice)
- Schematic capture and netlist management in OrCAD
- Bare-metal / register-level STM32 firmware development
- SDIO peripheral driver development
- FPGA RTL design in Verilog
- Testbench writing and simulation (Icarus Verilog + GTKWave)
- MCU to FPGA hardware/software co-design and interfacing
- Professional documentation and repository organization for portfolio use
