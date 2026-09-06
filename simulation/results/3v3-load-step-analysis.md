# 3.3 V Rail Load-Step Analysis

A simplified PSpice transient model was used to evaluate the response of the 3.3 V rail to a sudden increase in load current.

## Model

- Ideal source: 3.3 V
- Equivalent source impedance: 0.2 ohm
- Output capacitance: 10 uF
- Load current:
  - Initial: 20 mA
  - Step: 200 mA
  - Step begins: 2 ms
  - High-load duration: 4 ms
  - Rise/fall time: 10 us

This model is intended to represent rail behavior under a load step and is not a detailed transistor-level model of the AMS1117 regulator.

## Result

The simulated rail voltage is approximately:

- 3.296 V at 20 mA load
- 3.260 V at 200 mA load

This corresponds to approximately 36 mV of load-step droop.

The result is consistent with the simplified source-impedance model:

**Voltage droop = Change in current × Source impedance**

**Voltage droop = (0.20 A - 0.02 A) × 0.2 Ω = 0.036 V ≈ 36 mV**

The rail returns to its original level when the load decreases.

## Waveform

See [`3v3-load-step-waveform.png`](3v3-load-step-waveform.png).
