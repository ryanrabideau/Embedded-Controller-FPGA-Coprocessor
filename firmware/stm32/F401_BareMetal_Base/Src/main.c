/**
 * @file main.c
 * @brief Bare-metal STM32F401 + SDIO foundation
 */

#include <stdint.h>
#include "stm32f4xx.h"

/* ===================== Global flags ===================== */
volatile uint8_t  flag_1ms   = 0;
volatile uint8_t  flag_10ms  = 0;
volatile uint8_t  flag_100ms = 0;
volatile uint32_t tick_count = 0;

/* ===================== Clock ===================== */
void SystemClock_Config(void)
{
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));

    RCC->PLLCFGR = 0;
    RCC->PLLCFGR |= (16 << RCC_PLLCFGR_PLLM_Pos) |
                    (336 << RCC_PLLCFGR_PLLN_Pos) |
                    (1  << RCC_PLLCFGR_PLLP_Pos) |
                    (7  << RCC_PLLCFGR_PLLQ_Pos) |
                    RCC_PLLCFGR_PLLSRC_HSI;

    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_2WS;

    RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2)) |
                RCC_CFGR_HPRE_DIV1 |
                RCC_CFGR_PPRE1_DIV2 |
                RCC_CFGR_PPRE2_DIV1;

    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

/* ===================== Timer (1 kHz) ===================== */
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;
        tick_count++;
        flag_1ms = 1;
        if (tick_count % 10  == 0) flag_10ms  = 1;
        if (tick_count % 100 == 0) flag_100ms = 1;
    }
}

void Timer_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST;

    TIM2->PSC = 83;
    TIM2->ARR = 999;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->EGR |= TIM_EGR_UG;
    TIM2->SR = 0;

    NVIC_ClearPendingIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 5);
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2->CR1 |= TIM_CR1_CEN;
}

/* ===================== UART (kept for future use) ===================== */
void UART_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER3);
    GPIOA->MODER |=  (2 << GPIO_MODER_MODER2_Pos) | (2 << GPIO_MODER_MODER3_Pos);

    GPIOA->AFR[0] &= ~(0xFF << 8);
    GPIOA->AFR[0] |=  (7 << 8) | (7 << 12);

    USART2->BRR = 729;  // 115200 @ 84 MHz
    USART2->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void UART_SendByte(uint8_t b)
{
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR = b;
}

void UART_SendString(const char *s)
{
    while (*s) UART_SendByte(*s++);
}

/* ===================== SDIO ===================== */
void SDIO_GPIO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;

    // PC8-PC12 + PD2 → AF mode
    GPIOC->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9 |
                      GPIO_MODER_MODER10 | GPIO_MODER_MODER11 | GPIO_MODER_MODER12);
    GPIOC->MODER |=  (2U << GPIO_MODER_MODER8_Pos) | (2U << GPIO_MODER_MODER9_Pos) |
                     (2U << GPIO_MODER_MODER10_Pos)| (2U << GPIO_MODER_MODER11_Pos)|
                     (2U << GPIO_MODER_MODER12_Pos);

    GPIOD->MODER &= ~(GPIO_MODER_MODER2);
    GPIOD->MODER |=  (2U << GPIO_MODER_MODER2_Pos);

    // High speed
    GPIOC->OSPEEDR |= (3U << GPIO_OSPEEDR_OSPEED8_Pos) | (3U << GPIO_OSPEEDR_OSPEED9_Pos) |
                      (3U << GPIO_OSPEEDR_OSPEED10_Pos)| (3U << GPIO_OSPEEDR_OSPEED11_Pos)|
                      (3U << GPIO_OSPEEDR_OSPEED12_Pos);
    GPIOD->OSPEEDR |= (3U << GPIO_OSPEEDR_OSPEED2_Pos);

    // AF12
    GPIOC->AFR[1] &= ~((0xFU << 0) | (0xFU << 4) | (0xFU << 8) | (0xFU << 12) | (0xFU << 16));
    GPIOC->AFR[1] |=  (12U << 0) | (12U << 4) | (12U << 8) | (12U << 12) | (12U << 16);

    GPIOD->AFR[0] &= ~(0xFU << 8);
    GPIOD->AFR[0] |=  (12U << 8);
}

void SDIO_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SDIOEN;

    SDIO->POWER = 0x00;
    SDIO->CLKCR = 0x00;

    SDIO->POWER = 0x03;                     // Power ON
    for (volatile int i = 0; i < 2000; i++);

    // Slow clock for initialization (~400 kHz)
    // 84 MHz / (208 + 2) ≈ 400 kHz
    SDIO->CLKCR = (208 << 0) |              // CLKDIV
                  (1   << 8) |              // CLKEN
                  (0   << 11);              // 1-bit mode
}

void SDIO_ClearFlags(void)
{
    SDIO->ICR = 0x1FE00FFF;
}

uint32_t SDIO_GetResponse(void)
{
    return SDIO->RESP1;
}

// response_type: 0 = none, 1 = short, 3 = long
uint8_t SDIO_SendCommand(uint8_t cmd, uint32_t arg, uint8_t response_type)
{
    SDIO_ClearFlags();
    SDIO->ARG = arg;

    uint32_t cmdreg = (cmd & 0x3F) | (1U << 10); // CPSMEN

    if (response_type == 1)
        cmdreg |= (1U << 6);
    else if (response_type == 3)
        cmdreg |= (3U << 6);

    SDIO->CMD = cmdreg;

    uint32_t timeout = 250000;

    if (response_type == 0) {
        while (!(SDIO->STA & SDIO_STA_CMDSENT) && --timeout);
        if (timeout == 0) return 1;
        SDIO->ICR = SDIO_STA_CMDSENT;
    }
    else {
        while (!(SDIO->STA & (SDIO_STA_CMDREND | SDIO_STA_CCRCFAIL | SDIO_STA_CTIMEOUT)) && --timeout);
        if (timeout == 0) return 1;

        if (SDIO->STA & (SDIO_STA_CTIMEOUT | SDIO_STA_CCRCFAIL)) {
            SDIO_ClearFlags();
            return 2;
        }
        SDIO->ICR = SDIO_STA_CMDREND | SDIO_STA_CCRCFAIL | SDIO_STA_CTIMEOUT;
    }
    return 0; // success
}

uint8_t SD_InitCard(void)
{
    uint32_t resp;
    uint32_t timeout;

    // 1. CMD0 - GO_IDLE_STATE
    if (SDIO_SendCommand(0, 0, 0) != 0)
        return 1;

    // Small delay
    for (volatile int i = 0; i < 10000; i++);

    // 2. CMD8 - SEND_IF_COND (VHS = 2.7-3.6V, check pattern 0xAA)
    if (SDIO_SendCommand(8, 0x000001AA, 1) != 0)
        return 2;

    resp = SDIO_GetResponse();
    if ((resp & 0xFF) != 0xAA)          // check pattern
        return 3;

    // 3. ACMD41 loop (CMD55 + ACMD41)
    timeout = 1000;
    do {
        // CMD55 - APP_CMD
        if (SDIO_SendCommand(55, 0, 1) != 0)
            return 4;

        // ACMD41 - SD_SEND_OP_COND (HCS = 1 for SDHC)
        if (SDIO_SendCommand(41, 0x40FF8000, 1) != 0)
            return 5;

        resp = SDIO_GetResponse();
        timeout--;
    } while (((resp & (1UL << 31)) == 0) && timeout);  // wait until busy bit clears

    if (timeout == 0)
        return 6;   // card did not become ready

    // 4. CMD2 - ALL_SEND_CID (long response)
    if (SDIO_SendCommand(2, 0, 3) != 0)
        return 7;

    // 5. CMD3 - SEND_RELATIVE_ADDR
    if (SDIO_SendCommand(3, 0, 1) != 0)
        return 8;

    uint32_t rca = SDIO_GetResponse() & 0xFFFF0000;

    // 6. CMD7 - SELECT_CARD
    if (SDIO_SendCommand(7, rca, 1) != 0)
        return 9;

    // 7. ACMD6 - SET_BUS_WIDTH (4-bit)
    if (SDIO_SendCommand(55, rca, 1) != 0)
        return 10;

    if (SDIO_SendCommand(6, 2, 1) != 0)   // 2 = 4-bit mode
        return 11;

    // Switch SDIO peripheral to 4-bit mode
    SDIO->CLKCR |= (1U << 11);            // WIDBUS = 01 (4-bit)

    // Optionally increase clock speed here later

    return 0;   // success
}

/* ===================== FPGA Interface ===================== */

void FPGA_GPIO_Init(void)
{
    // Enable GPIOB clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // PB0 (CLK), PB1 (CS), PB2 (DATA0), PB3 (DATA1),
    // PB8 (DATA2), PB9 (DATA3) → Output
    // PB12 (IRQ) → Input

    // Clear mode bits first
    GPIOB->MODER &= ~(
        (3U <<  0) |  // PB0
        (3U <<  2) |  // PB1
        (3U <<  4) |  // PB2
        (3U <<  6) |  // PB3
        (3U << 16) |  // PB8
        (3U << 18) |  // PB9
        (3U << 24)    // PB12
    );

    // Set outputs
    GPIOB->MODER |= (
        (1U <<  0) |  // PB0 CLK  - output
        (1U <<  2) |  // PB1 CS   - output
        (1U <<  4) |  // PB2 D0   - output
        (1U <<  6) |  // PB3 D1   - output
        (1U << 16) |  // PB8 D2   - output
        (1U << 18)    // PB9 D3   - output
    );
    // PB12 remains input (00)

    // High speed for the bus pins
    GPIOB->OSPEEDR |= (
        (3U <<  0) | (3U <<  2) | (3U <<  4) | (3U <<  6) |
        (3U << 16) | (3U << 18)
    );

    // No pull-ups needed for outputs; weak pull-up on IRQ is optional
    GPIOB->PUPDR &= ~(3U << 24);
    GPIOB->PUPDR |=  (1U << 24);   // Pull-up on PB12 (IRQ)

    // Initial state: CS high (inactive), CLK low
    GPIOB->BSRR = (1U << 1);       // CS = 1
    GPIOB->BSRR = (1U << 16);      // CLK = 0
}

void FPGA_SetData(uint8_t data)
{
    // data is 4-bit value
    // DATA0 = PB2, DATA1 = PB3, DATA2 = PB8, DATA3 = PB9

    // Clear the four data bits first
    GPIOB->BSRR = (1U << 18) | (1U << 19) | (1U << 24) | (1U << 25); // reset PB2,3,8,9

    if (data & 0x01) GPIOB->BSRR = (1U << 2);   // DATA0
    if (data & 0x02) GPIOB->BSRR = (1U << 3);   // DATA1
    if (data & 0x04) GPIOB->BSRR = (1U << 8);   // DATA2
    if (data & 0x08) GPIOB->BSRR = (1U << 9);   // DATA3
}

void FPGA_ClockPulse(void)
{
    GPIOB->BSRR = (1U << 0);               // CLK = 1
    for (volatile int i = 0; i < 10; i++); // tiny delay
    GPIOB->BSRR = (1U << 16);              // CLK = 0
}

void FPGA_StartCapture(void)
{
    GPIOB->BSRR = (1U << 17);              // CS = 0 (active)
}

void FPGA_StopCapture(void)
{
    GPIOB->BSRR = (1U << 1);               // CS = 1 (inactive)
}

uint8_t FPGA_IRQ_Read(void)
{
    return (GPIOB->IDR & (1U << 12)) ? 1 : 0;
}

// Simple helper: send one 4-bit nibble with clock
void FPGA_WriteNibble(uint8_t nibble)
{
    FPGA_SetData(nibble & 0x0F);
    FPGA_ClockPulse();
}

/* ===================== Main ===================== */
int main(void)
{
    SystemClock_Config();
    Timer_Init();
    UART_Init();

    SDIO_GPIO_Init();
    SDIO_Init();

    FPGA_GPIO_Init();

    // LED PA5
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER = (GPIOA->MODER & ~(3U << 10)) | (1U << 10);

    // Simple SDIO test - send CMD0
    volatile uint8_t sd_status = SD_InitCard();
    (void)sd_status;   // prevent unused-variable warning

    // ========== FPGA Test Sequence ==========
    FPGA_StartCapture();

    // Send 12 test nibbles
    FPGA_WriteNibble(0x1);
    FPGA_WriteNibble(0x2);
    FPGA_WriteNibble(0x3);
    FPGA_WriteNibble(0x4);
    FPGA_WriteNibble(0x5);
    FPGA_WriteNibble(0x6);
    FPGA_WriteNibble(0x7);
    FPGA_WriteNibble(0x8);
    FPGA_WriteNibble(0x9);
    FPGA_WriteNibble(0xA);
    FPGA_WriteNibble(0xB);
    FPGA_WriteNibble(0xC);

    FPGA_StopCapture();
    // ========================================

    while (1)
    {
        if (flag_100ms) {
            flag_100ms = 0;

            // Blink fast if IRQ is high, slow if IRQ is low
            if (FPGA_IRQ_Read()) {
                GPIOA->ODR ^= (1 << 5);          // fast blink (every 100 ms)
            } else {
                // slow blink – only toggle every 500 ms
                static uint8_t slow_div = 0;
                if (++slow_div >= 5) {
                    slow_div = 0;
                    GPIOA->ODR ^= (1 << 5);
                }
            }
        }
    }
}

void HardFault_Handler(void)
{
    while (1);
}
