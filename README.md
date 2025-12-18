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
```

## Effects Summary

| Effect            | Description                                  | Visual Pattern |
|-------------------|----------------------------------------------|----------------|
| Knight Rider      | Classic scanning LED moving back and forth   | `[*---] → [-*--] → [--*-] → [---*] → back` |
| Wave              | Progressive fill then empty                  | `[*---] → [**--] → [***-] → [****] → empty` |
| Alternate Flash   | Even/odd LEDs alternate                      | `[*-*-] ↔ [-*-*]` |
| Converge          | Outer to inner LED pairs                     | `[*--*] ↔ [-**-]` |
| Binary Counter    | Counts 0–15 in binary                        | Displays binary numbers on 4 LEDs |
| Sparkle           | Pseudo-random twinkling                      | Random patterns using LFSR |
| Breathe           | Fade in/out (software PWM)                   | All LEDs pulse together |
| Cascade           | Two adjacent LEDs rotate                     | `[**--] → [-**-] → [--**] → [*--*]` |
