# Project Requirements

## System Objective

Develop a 4-layer embedded controller combining an STM32F401 microcontroller, Lattice iCE40 FPGA co-processor, and microSD interface.

The project demonstrates FPGA-assisted deterministic data capture, embedded system control, signal-integrity-aware PCB design, multi-rail power architecture, bare-metal firmware, and RTL development.

## Functional Requirements

### STM32 Controller
- Use an STM32F401 microcontroller as the primary system controller.
- Provide UART for debugging and system status.
- Provide a synchronous 4-bit interface between the STM32 and FPGA.
- Provide a 4-bit SDIO interface for microSD.
- Implement selected peripheral drivers directly at the register level.

### FPGA Co-Processor
- Use a Lattice iCE40UP5K FPGA.
- Implement deterministic parallel data capture and buffering in RTL.
- Provide an interrupt mechanism to the STM32.
- Verify FPGA functionality using a self-checking simulation testbench.

### Data Storage Interface
- Include a microSD connector.
- Provide a 4-bit SDIO hardware interface.
- Implement the SDIO initialization sequence in STM32 firmware.
- Reserve block-level read/write and filesystem functionality for future development.

## PCB Requirements

- Use a 4-layer FR-4 PCB.
- Include a continuous ground reference plane.
- Provide dedicated 3.3 V and 1.2 V power distribution.
- Apply a 50 Ω single-ended routing target to selected high-speed interfaces.
- Maintain clean return-current paths.
- Use source series termination where appropriate.
- Consider timing relationships and trace lengths on synchronous interfaces.
- Complete PCB design-rule checking with no unrouted connections or DRC errors.

## Power Requirements

- Provide a regulated 3.3 V system rail.
- Provide a regulated 1.2 V FPGA core rail.
- Include local decoupling and bulk capacitance.
- Document the system power architecture.
- Perform a simplified PSpice load-step analysis of the 3.3 V rail.

## Firmware Requirements

- Develop STM32F401 firmware in C.
- Implement direct register-level peripheral configuration for selected drivers.
- Implement UART-based debug output.
- Implement the MCU to FPGA synchronous interface.
- Implement the SDIO initialization sequence.

## FPGA / RTL Requirements

- Develop the FPGA logic in Verilog.
- Use modular RTL design.
- Implement a deterministic parallel data-capture and buffering function.
- Develop a self-checking functional verification testbench.
- Capture and document simulation waveforms.

## Documentation Requirements

The repository should contain:

- System architecture documentation
- Power architecture documentation
- Schematic documentation
- PCB layout evidence
- PCB stackup
- Impedance calculations and routing rationale
- Power-rail simulation results
- Firmware documentation
- FPGA/RTL documentation
- FPGA verification results
- Project status, limitations, and future work

## Validation Boundary

The project was completed as a design, firmware, RTL, and simulation portfolio project. The PCB was not fabricated, so target-board power-up, physical MCU to FPGA communication, and microSD operation were not validated on the completed PCB.
