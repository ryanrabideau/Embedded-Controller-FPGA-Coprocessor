# FPGA

Parallel Data Capture Engine for the Lattice iCE40.

## Contents

- `rtl/parallel_capture.v` – Main capture module
- `testbench/tb_parallel_capture.v` – Simulation testbench
- `simulation/waveforms/` – GTKWave screenshots

## Function

The module captures 4-bit parallel data on the rising edge of the MCU-supplied clock while chip-select is active. It maintains a simple internal buffer and raises an interrupt when a threshold is reached.

## Simulation

Simulated with Icarus Verilog and viewed in GTKWave.
