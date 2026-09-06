# Simulation

PSpice analysis used to evaluate the 3.3 V power rail under a transient load condition.

## 3.3 V Load-Step Analysis

A simplified power-rail model was created to evaluate voltage droop when the load current increases from 20 mA to 200 mA.

The model includes:

- 3.3 V source
- 0.2 Ω equivalent source impedance
- 10 µF output capacitance
- Pulsed 20 mA to 200 mA load
- 10 µs load transition time

The simulation produced approximately 36 mV of voltage droop during the load step, with the rail recovering when the load returned to 20 mA.

This is a simplified rail-level model intended for transient power-integrity analysis. It is not a transistor-level or manufacturer-model simulation of the AMS1117 regulator.

## Results

- [`3.3 V Load-Step Analysis`](results/3v3-load-step-analysis.md)
- [`Load-Step Waveform`](results/3v3-load-step-waveform.png)

## Tools

- OrCAD Capture
- PSpice
