# Bare Metal Toggle LED Project for STM32F103C8T6

This project demonstrates how to configure and control an LED connected to pin 13 of GPIOC on an STM32F103C8T6 microcontroller using bare-metal programming.
## Project Overview

The goal of this project is to show how to directly configure a GPIO peripheral and toggle an LED's state by manipulating hardware registers.

## Table of Contents
- [Overview](#project-overview)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [Code Explanation](#code-explanation)
- [Build and Run Instructions](#build-and-run-instructions)
- [References](#references)

## Requirements

To compile and run this project, you need:

- **Tools**:
  - STM32CubeIDE or any compatible ARM Cortex-M development environment.
  - A programmer such as ST-Link.
- **Hardware**:
  - STM32F103C8T6 microcontroller..

## Project Structure

The project contains the following files:

- `main.c`: The main source code file with the logic to toggle the LED.
- `Makefile` (optional): A file for building the project from the command line.

## Code Explanation

Below is the main code with detailed explanations:

```c
#include <stdint.h>

// Base and offset address definitions for peripheral registers
#define PERIPH_BASE          (0x40000000UL)       // Base address for all peripherals
#define APB2PERIPH_OFFSET    (0x00011000UL)       // Offset for APB2 peripherals
#define APB2PERIPH_BASE      (PERIPH_BASE + APB2PERIPH_OFFSET) // Base address for APB2 peripherals

#define GPIOC_OFFSET         (0x0000UL)           // Offset for GPIOC peripheral
#define GPIOC_BASE           (APB2PERIPH_BASE + GPIOC_OFFSET) // Base address for GPIOC

#define RCC_OFFSET           (0x00010000UL)       // Offset for RCC (Reset and Clock Control)
#define RCC_BASE             (APB2PERIPH_BASE + RCC_OFFSET) // Base address for RCC

#define APB2_EN_R_OFFSET     (0x18UL)             // Offset for APB2 peripheral clock enable register
#define RCC_APB2EN_R         (*(volatile unsigned int *)(RCC_BASE + APB2_EN_R_OFFSET)) // Clock enable register for APB2 peripherals

#define MODE_R_OFFSET        (0x04)                // Offset for GPIO mode register
#define GPIOC_MODE_R         (*(volatile unsigned int *)(GPIOC_BASE + MODE_R_OFFSET)) // Mode register for GPIOC

#define OD_R_OFFSET          (0x0CUL)              // Offset for GPIO output data register
#define GPIOC_OD_R           (*(volatile unsigned int *)(GPIOC_BASE + OD_R_OFFSET)) // Output data register for GPIOC

#define GPIOCEN              (1U << 4)             // Enable bit for GPIOC (bit 4 in RCC_APB2EN_R)
#define PIN_13               (1U << 13)            // Bit position for pin 13 in GPIOC
#define LED_PIN              PIN_13                // Define LED pin as pin 13

int main(void) {
    // Enable the clock for GPIOC by setting the GPIOCEN bit in RCC_APB2EN_R
    RCC_APB2EN_R |= GPIOCEN;

    // Configure pin 13 of GPIOC as an output (general purpose output mode)
    // Set mode bits for pin 13 (mode is set to output)
    GPIOC_MODE_R |= (1U << 21); // Set bit 21 to
```

### Code Details
- **Clock Enable**: `RCC_APB2EN_R |= GPIOCEN;` enables the clock for GPIOC so it can be used.
- **Pin Configuration**: `GPIOC_MODE_R |= (1U << 21);` sets pin 13 as an output.
- **Toggle Pin State**: `GPIOC_OD_R ^= LED_PIN;` toggles the state of pin 13, turning the LED on or off.
- **Delay Loop**: The `for` loop provides a simple delay to make the LED blink at a human-visible rate.

## Build and Run Instructions

1. **Import the project** into STM32CubeIDE or compile manually with `make`.
2. **Program the microcontroller** using ST-Link or another compatible tool.
3. **Verify the output**: The LED connected to pin 13 of GPIOC should blink.

## References

- [STM32F103C8T6 Datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)
- [STM32F103 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32bit-mcus-stmicroelectronics.pdf)
