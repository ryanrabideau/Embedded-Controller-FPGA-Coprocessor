# Project Milestones

## Phase 1 — System Definition
- [x] Define system architecture and use case
- [x] Define MCU / FPGA / storage partitioning
- [x] Establish scope boundaries (no DDR / SerDes / PCIe)

## Phase 2 — Component Selection
- [x] Select STM32F401
- [x] Select Lattice iCE40UP5K
- [x] Select microSD connector
- [x] Define multi-rail power approach (3.3 V + 1.2 V)

## Phase 3 — Schematic Design
- [x] Create Power page
- [x] Create MCU page
- [x] Create FPGA page
- [x] Create MicroSD page
- [x] Complete schematic DRC

## Phase 4 — Power Simulation
- [x] Perform PSpice analysis on key rails
- [x] Document power tree and decoupling strategy

## Phase 5 — PCB Layout
- [x] Define 4-layer stackup
- [x] Calculate and constrain 50 Ω microstrip
- [x] Place components
- [x] Route high-speed interfaces (SDIO + MCU–FPGA bus)
- [x] Apply series termination
- [x] Complete layout DRC

## Phase 6 — Firmware
- [x] Bare-metal clock and timer foundation
- [x] UART driver (register-level)
- [x] Register-level SDIO initialization sequence
- [x] MCU ↔ FPGA communication driver

## Phase 7 — FPGA / RTL
- [x] Parallel Data Capture Engine (Verilog)
- [x] Testbench
- [x] Simulation waveforms (GTKWave)

## Phase 8 — Documentation & Repository
- [x] Top-level README updated to completed status
- [x] Project management status files updated
- [ ] Additional technical documentation and assets (in progress)
