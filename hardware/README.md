# Hardware

Hardware design documentation for the Embedded Controller with FPGA Co-Processor.

## Hardware Overview

The controller is implemented as a 4-layer FR-4 PCB integrating an STM32F401 microcontroller, Lattice iCE40UP5K FPGA co-processor, and microSD interface.

Key design features include:

- STM32F401RET6 microcontroller
- Lattice iCE40UP5K-SG48 FPGA
- 4-bit SDIO microSD interface
- 4-layer PCB stackup
- 50 Ω single-ended controlled-impedance routing target
- 3.3 V and 1.2 V power rails
- 22 Ω source series termination on selected high-speed digital interfaces
- Continuous ground plane and return-path-aware routing

## Schematic

The complete four-page schematic is available here:

- [`controller-schematic.pdf`](schematic/controller-schematic.pdf)

Individual schematic views:

- [`FPGA`](schematic/screenshots/fpga-schematic.png)
- [`MCU`](schematic/screenshots/mcu-schematic.png)
- [`Power`](schematic/screenshots/power-schematic.png)
- [`MicroSD`](schematic/screenshots/microsd-schematic.png)

## PCB

PCB design documentation and routing evidence:

- [`PCB Stackup`](pcb/stackup.md)
- [`Top-Layer Routing`](pcb/screenshots/pcb-top-routing.png)
- [`Bottom-Layer Routing`](pcb/screenshots/pcb-bottom-routing.png)
- [`Combined Routing`](pcb/screenshots/pcb-combined-routing.png)
- [`PCB DRC Status`](pcb/screenshots/pcb-drc-status.png)

The completed layout contains 47 placed components, 0 unrouted connections, and 0 DRC errors.

## Design Status

The schematic and PCB layout are complete, but the board has not been fabricated. PCB screenshots and design-rule results therefore represent CAD-level design verification rather than physical hardware validation.
