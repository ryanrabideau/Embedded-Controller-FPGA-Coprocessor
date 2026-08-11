# Firmware

Bare-metal firmware for the STM32F401 master controller.

Planned functionality includes:

- GPIO
- UART
- SPI / MCU-FPGA communication
- SDIO
- Interrupt handling
- System control

Core peripheral drivers will emphasize direct register-level configuration rather than heavy abstraction through HAL.
