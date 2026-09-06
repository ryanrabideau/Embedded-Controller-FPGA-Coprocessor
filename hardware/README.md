# Hardware

This folder contains the hardware design files and documentation for the Embedded Controller with FPGA Co-Processor.

## Contents

- **schematic/** – OrCAD schematic source and exports
- **pcb/** – PCB layout, stackup definition, and screenshots
- **libraries/** – Custom symbols and footprints (if exported)
- **bom/** – Bill of materials and critical component notes

## Design Summary

- 4-layer FR-4 PCB
- STM32F401 + Lattice iCE40UP5K + microSD (4-bit SDIO)
- Controlled-impedance routing (50 Ω microstrip target)
- Multi-rail power (3.3 V and 1.2 V)
- Source series termination on key interfaces
- Continuous ground plane and return-path aware layout
