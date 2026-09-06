# Firmware

Bare-metal / register-level firmware for the STM32F401.

## Contents

- `stm32/F401_BareMetal_Base/` – Complete STM32CubeIDE project

## Features Implemented

- System clock configuration (84 MHz from HSI + PLL)
- 1 kHz timer-based scheduler
- Register-level UART driver
- Register-level SDIO initialization sequence
- MCU to FPGA 4-bit communication driver
- GPIO control and basic LED status

## Notes

- Written primarily with direct register access (minimal HAL usage)
- Developed and tested on NUCLEO-F401RE
- SDIO and FPGA interface drivers are included and functional at the initialization / communication level
