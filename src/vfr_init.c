#include "vfr_init.h"
#include "src\src\hardware\hardware.h"

#include "stdDatatypes"

/* Now we need a nice struct, to define virtual function register. */

typedef volatile struct {
    uint32_t pin0 : 1;  // Bit 0: LED Rot
    uint32_t pin1 : 1;  // Bit 1: LED Grün
    uint32_t pin2 : 1;  // Bit 2: LED Blau
    uint32_t mode : 2;  // Bit 3-4: Modus (z.B. 00=Input, 01=Output)
    uint32_t rsvd : 27; // Die restlichen 27 Bits auffüllen (für 32-Bit)
} gpio_reg_t;

#define GPIO_BASE_ADDR 0x3FF44000 

void led_init() {
    gpio_reg_t *rGPIO = (gpio_reg_t*)GPIO_BASE_ADDR;

    rGPIO->mode = 1;   // Setzt Modus auf Output
    rGPIO->pin0 = 1;   // Rote LED an!
    rGPIO->pin1 = 0;   // Grüne LED aus
}
