# FPGA

Parallel Data Capture Engine implemented in Verilog for the Lattice iCE40 FPGA co-processor.

## Contents

- [`rtl/parallel_capture.v`](rtl/parallel_capture.v) – Parallel capture RTL module
- [`testbench/tb_parallel_capture.v`](testbench/tb_parallel_capture.v) – Self-checking simulation testbench
- [`waveforms/`](waveforms/) – GTKWave simulation screenshots

## Function

The Parallel Data Capture Engine receives 4-bit parallel data from the STM32 and captures one sample on each rising edge of the MCU-supplied clock while chip select is active.

The module includes:

- 16-entry × 4-bit internal capture buffer
- 4-bit write pointer
- Sample counter
- Interrupt output (`irq`)
- Interrupt assertion when the 8th sample is captured
- Automatic capture-state reset when chip select is released

Resetting the capture state between transactions ensures that each new capture session begins from a known state.

## Verification

The RTL was simulated using Icarus Verilog and inspected using GTKWave.

The self-checking testbench verifies that:

- IRQ remains low for the first 7 captured samples
- IRQ asserts when the 8th sample is captured
- IRQ remains asserted during continued capture
- Releasing chip select clears the interrupt and capture state
- The sample counter and write pointer return to zero
- A second capture session starts from a clean state
- IRQ threshold behavior remains correct across repeated capture sessions

The current testbench completes with:

```text
PASS: All parallel capture tests passed.
```

Simulation waveforms are available in [`waveforms/`](waveforms/).
