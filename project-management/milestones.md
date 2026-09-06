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
- [x] Perform simplified 3.3 V rail load-step analysis in PSpice
- [x] Document load-step assumptions and simulation results
- [x] Document power tree and decoupling strategy

## Phase 5 — PCB Layout
- [x] Define 4-layer stackup
- [x] Calculate and constrain 50 Ω single-ended microstrip routing target
- [x] Place components
- [x] Route high-speed interfaces (SDIO + MCU to FPGA bus)
- [x] Apply series termination
- [x] Complete layout DRC with 0 unrouted connections and 0 DRC errors

## Phase 6 — Firmware
- [x] Bare-metal clock and timer foundation
- [x] UART driver (register-level)
- [x] Verify UART output at 115200 baud
- [x] Implement register-level SDIO initialization sequence
- [x] Implement MCU to FPGA synchronous 4-bit interface driver

## Phase 7 — FPGA / RTL
- [x] Implement Parallel Data Capture Engine in Verilog
- [x] Create self-checking testbench
- [x] Verify RTL simulation using Icarus Verilog
- [x] Inspect simulation waveforms using GTKWave

## Phase 8 — Documentation & Repository
- [x] Update top-level README
- [x] Add schematic and PCB design evidence
- [x] Add FPGA verification evidence
- [x] Add PSpice analysis and results
- [x] Document architecture, current status, and project limitations
