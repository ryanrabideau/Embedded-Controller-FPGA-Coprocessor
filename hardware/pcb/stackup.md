# PCB Stackup & Impedance

## 4-Layer Stackup

The board uses a standard 1.6 mm 4-layer FR-4 stackup:

- **Layer 1 (TOP)** – Signal layer, 1 oz copper. Components and high-speed signals live here.
- **Prepreg** – approximately 0.18 mm, εr ≈ 4.5
- **Layer 2 (GND)** – Solid unbroken ground plane, 1 oz copper
- **Core** – approximately 1.15 mm
- **Layer 3 (POWER)** – Power plane (3.3 V and 1.2 V regions), 1 oz copper
- **Prepreg** – approximately 0.18 mm
- **Layer 4 (BOTTOM)** – Signal layer, 1 oz copper

**Total thickness:** approximately 1.6 mm

## Controlled Impedance

**Target:** 50 Ω single-ended microstrip on Layer 1, referenced to Layer 2 (GND)

**Calculated trace width:** 0.30 – 0.31 mm (~12 mil)

This width was applied as a design rule to the following nets:
- SDIO_CLK, SDIO_CMD, SDIO_D0–D3
- MCU to FPGA bus (CLK, CS, DATA[3:0])

## Design Notes

- High-speed signals preferred on TOP layer over continuous GND plane
- 22 Ω series termination placed near the driver pins
- Strict ±10 mil length matching was not fully enforced (acceptable for the interface speeds used in this design)
