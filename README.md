# Zephyr nRF Connect SDK Projects

A collection of projects and examples for the **Nordic nRF5340** Development Kit 
using **Zephyr RTOS** and the **nRF Connect SDK**.

![nRF5340 DK](https://www.nordicsemi.com/-/media/Images/Products/DevKits/nRF53-Series/nRF5340-DK/nRF5340-DK.png)

## About This Repository

This repository contains various embedded projects demonstrating different 
features and peripherals of the nRF5340 SoC. Each project is self-contained 
with its own documentation, source code, and build configuration.

## Hardware Requirements

- **Board**: Nordic nRF5340 DK (PCA10095)
- **SDK**: nRF Connect SDK v2.x
- **Tools**: VS Code with nRF Connect Extension (recommended)

## Projects

| # | Project | Description | Status |
|---|---------|-------------|--------|
| 01 | [LED Light Show](./01_LED_Light_Show/) | Various LED animation effects using GPIO API | Done |
| 02 | [BLE Basics](./02_BLE_Basics/) | Introduction to Bluetooth Low Energy | Planned |
| 03 | [Bluetooth Peripheral](./03_Bluetooth_Peripheral/) | Custom BLE peripheral service | Planned |
| 04 | [I2C Sensors](./04_I2C_Sensors/) | Reading data from I2C sensors | Planned |
| 05 | [UART Communication](./05_UART_Communication/) | Serial communication examples | Planned |
| 06 | [PWM Control](./06_PWM_Control/) | PWM for LED dimming and motors | Planned |

## Getting Started

### Prerequisites

1. Install [nRF Connect SDK](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/installation.html)
2. Install [VS Code](https://code.visualstudio.com/) with nRF Connect Extension
3. Connect your nRF5340 DK via USB

### Building a Project

```bash
# Navigate to a project folder
cd 01_LED_Light_Show

# Build for nRF5340 DK (application core)
west build -b nrf5340dk_nrf5340_cpuapp

# Flash to device
west flash
