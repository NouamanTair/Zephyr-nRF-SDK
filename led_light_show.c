/*
 * LED Light Show for nRF5340 Development Kit
 * 
 * Description: This program demonstrates various LED animation effects
 *              using the 4 onboard LEDs of the nRF5340 DK.
 * 
 * Platform:    Nordic nRF5340 DK
 * RTOS:        Zephyr RTOS
 * Author:      [Your Name]
 * License:     MIT (or your preferred license)
 * 
 * Hardware Requirements:
 *   - nRF5340 Development Kit with 4 LEDs (LED0-LED3)
 * 
 * API Reference:
 *   - Zephyr GPIO API: https://docs.zephyrproject.org/latest/hardware/peripherals/gpio.html
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* ============================================================================
 * CONFIGURATION
 * ============================================================================
 * LED node definitions from DeviceTree.
 * These aliases (led0, led1, led2, led3) are defined in the board's .dts file.
 * For nRF5340 DK, they correspond to P0.28, P0.29, P0.30, P0.31
 */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

#define NUM_LEDS 4

/* 
 * GPIO specifications array for all LEDs.
 * GPIO_DT_SPEC_GET extracts the GPIO port, pin number, and flags
 * from the DeviceTree configuration.
 */
static const struct gpio_dt_spec leds[NUM_LEDS] = {
    GPIO_DT_SPEC_GET(LED0_NODE, gpios),
    GPIO_DT_SPEC_GET(LED1_NODE, gpios),
    GPIO_DT_SPEC_GET(LED2_NODE, gpios),
    GPIO_DT_SPEC_GET(LED3_NODE, gpios),
};

/* ============================================================================
 * TIMING DEFINITIONS
 * ============================================================================
 * Adjust these values to change animation speed
 */
#define FAST_DELAY_MS    50   /* Fast animations (sparkle, cascade) */
#define MEDIUM_DELAY_MS  100  /* Medium animations (knight rider, binary) */
#define SLOW_DELAY_MS    200  /* Slow animations (wave, converge) */

/* ============================================================================
 * UTILITY FUNCTIONS
 * ============================================================================
 * Basic LED control functions used by all effects
 */

/**
 * @brief Turn off all LEDs
 * 
 * Sets all 4 LEDs to inactive state (LOW)
 */
static void all_leds_off(void)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_pin_set_dt(&leds[i], 0);
    }
}

/**
 * @brief Turn on all LEDs
 * 
 * Sets all 4 LEDs to active state (HIGH)
 */
static void all_leds_on(void)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_pin_set_dt(&leds[i], 1);
    }
}

/**
 * @brief Set a specific LED state
 * 
 * @param index LED index (0-3)
 * @param state true = ON, false = OFF
 */
static void set_led(int index, bool state)
{
    if (index >= 0 && index < NUM_LEDS) {
        gpio_pin_set_dt(&leds[index], state ? 1 : 0);
    }
}

/* ============================================================================
 * LED EFFECTS
 * ============================================================================
 * Collection of visual effects for the 4 LEDs
 */

/**
 * @brief Knight Rider Effect
 * 
 * Classic scanning LED effect, moving back and forth.
 * Pattern: [*---] -> [-*--] -> [--*-] -> [---*] -> [--*-] -> ...
 * 
 * @param cycles Number of complete back-and-forth cycles
 */
static void effect_knight_rider(int cycles)
{
    printf("[Effect] Knight Rider\n");
    
    for (int c = 0; c < cycles; c++) {
        /* Forward sweep: LED 0 to LED 3 */
        for (int i = 0; i < NUM_LEDS; i++) {
            all_leds_off();
            set_led(i, true);
            k_msleep(MEDIUM_DELAY_MS);
        }
        /* Backward sweep: LED 2 to LED 0 */
        for (int i = NUM_LEDS - 2; i >= 0; i--) {
            all_leds_off();
            set_led(i, true);
            k_msleep(MEDIUM_DELAY_MS);
        }
    }
    all_leds_off();
}

/**
 * @brief Wave Effect
 * 
 * Progressive fill and empty effect.
 * Fill:  [*---] -> [**--] -> [***-] -> [****]
 * Empty: [****] -> [-***] -> [--**] -> [---*] -> [----]
 * 
 * @param cycles Number of complete fill/empty cycles
 */
static void effect_wave(int cycles)
{
    printf("[Effect] Wave\n");
    
    for (int c = 0; c < cycles; c++) {
        /* Progressive fill from LED 0 to LED 3 */
        for (int i = 0; i < NUM_LEDS; i++) {
            set_led(i, true);
            k_msleep(SLOW_DELAY_MS);
        }
        /* Progressive empty from LED 0 to LED 3 */
        for (int i = 0; i < NUM_LEDS; i++) {
            set_led(i, false);
            k_msleep(SLOW_DELAY_MS);
        }
    }
}

/**
 * @brief Alternate Flash Effect
 * 
 * Alternates between even and odd LEDs.
 * Pattern: [*-*-] <-> [-*-*]
 * 
 * @param cycles Number of alternation cycles
 */
static void effect_alternate_flash(int cycles)
{
    printf("[Effect] Alternate Flash\n");
    
    for (int c = 0; c < cycles; c++) {
        /* Even LEDs ON (0, 2), Odd LEDs OFF (1, 3) */
        set_led(0, true);
        set_led(1, false);
        set_led(2, true);
        set_led(3, false);
        k_msleep(SLOW_DELAY_MS);
        
        /* Odd LEDs ON (1, 3), Even LEDs OFF (0, 2) */
        set_led(0, false);
        set_led(1, true);
        set_led(2, false);
        set_led(3, true);
        k_msleep(SLOW_DELAY_MS);
    }
    all_leds_off();
}

/**
 * @brief Converge Effect
 * 
 * LEDs light from outside to inside and vice versa.
 * Pattern: [*--*] <-> [-**-]
 * 
 * @param cycles Number of convergence cycles
 */
static void effect_converge(int cycles)
{
    printf("[Effect] Converge\n");
    
    for (int c = 0; c < cycles; c++) {
        all_leds_off();
        
        /* Outer LEDs ON (0 and 3) */
        set_led(0, true);
        set_led(3, true);
        k_msleep(SLOW_DELAY_MS);
        
        all_leds_off();
        
        /* Inner LEDs ON (1 and 2) */
        set_led(1, true);
        set_led(2, true);
        k_msleep(SLOW_DELAY_MS);
    }
    all_leds_off();
}

/**
 * @brief Binary Counter Effect
 * 
 * Displays numbers 0-15 in binary using the 4 LEDs.
 * LED0 = bit 0 (LSB), LED3 = bit 3 (MSB)
 * 
 * Example: 5 (0101) = LED0 ON, LED1 OFF, LED2 ON, LED3 OFF
 * 
 * @param cycles Number of complete 0-15 count cycles
 */
static void effect_binary_counter(int cycles)
{
    printf("[Effect] Binary Counter\n");
    
    for (int c = 0; c < cycles; c++) {
        for (int count = 0; count < 16; count++) {
            /* Extract each bit and set corresponding LED */
            set_led(0, (count & 0x01) != 0);  /* Bit 0 */
            set_led(1, (count & 0x02) != 0);  /* Bit 1 */
            set_led(2, (count & 0x04) != 0);  /* Bit 2 */
            set_led(3, (count & 0x08) != 0);  /* Bit 3 */
            k_msleep(MEDIUM_DELAY_MS);
        }
    }
    all_leds_off();
}

/**
 * @brief Sparkle Effect
 * 
 * Creates a pseudo-random twinkling pattern using a 
 * Linear Feedback Shift Register (LFSR) algorithm.
 * 
 * @param iterations Number of random pattern iterations
 */
static void effect_sparkle(int iterations)
{
    printf("[Effect] Sparkle\n");
    
    /* LFSR seed value */
    uint8_t pattern = 0x01;
    
    for (int i = 0; i < iterations; i++) {
        /* 
         * 4-bit LFSR (Linear Feedback Shift Register)
         * Generates pseudo-random sequence
         * Taps at positions 0 and 2 (XOR feedback)
         */
        uint8_t feedback = ((pattern ^ (pattern >> 2)) & 1);
        pattern = ((pattern >> 1) | (feedback << 3)) & 0x0F;
        
        /* Avoid all-off state */
        if (pattern == 0) {
            pattern = 0x05;
        }
        
        /* Apply pattern to LEDs */
        set_led(0, (pattern & 0x01) != 0);
        set_led(1, (pattern & 0x02) != 0);
        set_led(2, (pattern & 0x04) != 0);
        set_led(3, (pattern & 0x08) != 0);
        
        k_msleep(FAST_DELAY_MS);
    }
    all_leds_off();
}

/**
 * @brief Breathe Effect
 * 
 * Simulates a breathing/pulsing effect using software PWM.
 * All LEDs fade in and out together.
 * 
 * Note: This is a software PWM implementation. For smoother
 * results, consider using hardware PWM if available.
 * 
 * @param cycles Number of breath cycles
 */
static void effect_breathe(int cycles)
{
    printf("[Effect] Breathe\n");
    
    for (int c = 0; c < cycles; c++) {
        /* Fade IN: gradually increase ON time */
        for (int brightness = 0; brightness < 10; brightness++) {
            for (int pulse = 0; pulse < 5; pulse++) {
                all_leds_on();
                k_msleep(brightness);       /* ON time increases */
                all_leds_off();
                k_msleep(10 - brightness);  /* OFF time decreases */
            }
        }
        
        /* Fade OUT: gradually decrease ON time */
        for (int brightness = 10; brightness > 0; brightness--) {
            for (int pulse = 0; pulse < 5; pulse++) {
                all_leds_on();
                k_msleep(brightness);       /* ON time decreases */
                all_leds_off();
                k_msleep(10 - brightness);  /* OFF time increases */
            }
        }
    }
}

/**
 * @brief Cascade Effect
 * 
 * Two adjacent LEDs rotate around all 4 positions.
 * Pattern: [**--] -> [-**-] -> [--**] -> [*--*] -> ...
 * 
 * @param cycles Number of rotation cycles
 */
static void effect_cascade(int cycles)
{
    printf("[Effect] Cascade\n");
    
    for (int c = 0; c < cycles; c++) {
        for (int i = 0; i < NUM_LEDS; i++) {
            all_leds_off();
            /* Turn on current LED and next LED (with wrap-around) */
            set_led(i, true);
            set_led((i + 1) % NUM_LEDS, true);
            k_msleep(FAST_DELAY_MS);
        }
    }
    all_leds_off();
}

/* ============================================================================
 * MAIN FUNCTION
 * ============================================================================
 */

/**
 * @brief Application entry point
 * 
 * Initializes all 4 LEDs and runs through all effects in a loop.
 * 
 * @return 0 on success, negative error code on failure
 */
int main(void)
{
    int ret;

    printf("\n");
    printf("========================================\n");
    printf("    nRF5340 LED Light Show             \n");
    printf("    Zephyr RTOS Demo                   \n");
    printf("========================================\n\n");

    /* Initialize all 4 LEDs */
    for (int i = 0; i < NUM_LEDS; i++) {
        /* Check if GPIO port is ready */
        if (!gpio_is_ready_dt(&leds[i])) {
            printf("[ERROR] LED%d GPIO device not ready\n", i);
            return -1;
        }

        /* Configure GPIO pin as output (initially inactive/OFF) */
        ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_INACTIVE);
        if (ret < 0) {
            printf("[ERROR] Failed to configure LED%d (err=%d)\n", i, ret);
            return -1;
        }
        printf("[OK] LED%d initialized successfully\n", i);
    }

    printf("\n[START] Beginning light show sequence...\n\n");

    /* Main loop: cycle through all effects */
    while (1) {
        effect_knight_rider(3);
        k_msleep(500);

        effect_wave(2);
        k_msleep(500);

        effect_alternate_flash(6);
        k_msleep(500);

        effect_converge(4);
        k_msleep(500);

        effect_binary_counter(2);
        k_msleep(500);

        effect_sparkle(50);
        k_msleep(500);

        effect_breathe(2);
        k_msleep(500);

        effect_cascade(8);
        k_msleep(500);

        /* Grand Finale: rapid flashing */
        printf("[Effect] Grand Finale\n");
        for (int i = 0; i < 10; i++) {
            all_leds_on();
            k_msleep(50);
            all_leds_off();
            k_msleep(50);
        }
        
        printf("\n[LOOP] Restarting sequence...\n\n");
        k_msleep(1000);
    }

    return 0;
}
