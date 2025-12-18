# nRF5340 LED Light Show

A demonstration of various LED animation effects using the Zephyr RTOS GPIO API 
on the Nordic nRF5340 Development Kit.

## Hardware Requirements

- Nordic nRF5340 DK (PCA10095)
- 4 onboard LEDs (LED1-LED4)

## Building and Flashing

```bash
west build -b nrf5340dk_nrf5340_cpuapp
west flash
