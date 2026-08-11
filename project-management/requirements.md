# Project Requirements

## System Objective

Develop a 4-layer embedded controller that combines an STM32F401 microcontroller, Lattice iCE40 FPGA co-processor, and microSD storage interface.

The system is intended to demonstrate FPGA-assisted deterministic data capture, embedded system control, signal-integrity-aware PCB design, multi-rail power architecture, bare-metal firmware, and RTL development.

## Functional Requirements

### STM32 Controller
- Use an STM32F401 microcontroller as the primary system controller.
- Support UART for debugging and system status.
- Support communication between the STM32 and FPGA.
- Support microSD storage using SDIO.
- Implement core peripheral drivers primarily at the register level.

### FPGA Co-Processor
- Use a Lattice iCE40 FPGA.
- Implement a meaningful RTL function such as deterministic parallel data capture or buffering.
- Provide an interrupt or status mechanism for communication with the STM32.
- Verify FPGA functionality using a simulation testbench.

### Data Storage
- Include a microSD connector.
- Use 4-bit SDIO communication.
- Support data storage or logging functionality.

## PCB Requirements

- Use a 4-layer FR-4 PCB.
- Include a continuous ground reference plane.
- Provide dedicated power distribution.
- Apply controlled-impedance routing where appropriate.
- Maintain clean return-current paths.
- Use source termination where justified.
- Apply length matching to timing-sensitive buses where required.
- Pass electrical and physical design-rule checks.

## Power Requirements

- Provide a regulated 3.3 V system rail.
- Provide a regulated 1.2 V FPGA core rail.
- Include appropriate local decoupling and bulk capacitance.
- Document the system power tree.
- Analyze critical power rails using PSpice.

## Firmware Requirements

- Develop firmware in C for the STM32F401.
- Implement direct register-level peripheral configuration for selected drivers.
- Use interrupt-driven operation where appropriate.
- Implement MCU-to-FPGA communication.
- Implement basic SDIO functionality.
- Provide UART-based debug output.

## FPGA / RTL Requirements

- Develop RTL in SystemVerilog or Verilog.
- Use modular RTL design.
- Implement a deterministic data-capture or buffering function.
- Develop a functional verification testbench.
- Capture and document simulation waveforms.
- Define FPGA pin and timing constraints.

## Documentation Requirements

The repository should ultimately contain:

- System block diagram
- Power tree
- Schematic documentation
- PCB stackup
- Impedance calculations
- Signal integrity design rationale
- Power integrity simulation results
- Firmware architecture
- FPGA architecture
- Verification results
- Design decisions
- Lessons learned
