# Firmware

Bare-metal / register-level firmware for the STM32F401.

## Contents

- `stm32/F401_BareMetal_Base/` – Complete STM32CubeIDE project

## Features Implemented

- System clock configuration (84 MHz from HSI + PLL)
- 1 kHz timer-based scheduler
- Register-level UART driver
- Register-level SDIO initialization sequence
- MCU to FPGA synchronous 4-bit interface driver
- GPIO control and basic LED status

## Verification

- UART output was verified successfully at 115200 baud on the NUCLEO-F401RE
- FPGA interface firmware is implemented but was not physically validated with the target FPGA hardware
- SDIO initialization firmware is implemented but was not validated with the target microSD hardware

## Notes

- Written primarily with direct register access
- Developed using STM32CubeIDE
- Target-board end-to-end validation was not performed because the custom PCB was not fabricated
