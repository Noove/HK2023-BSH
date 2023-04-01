#pragma once

// Includes
#include <Arduino.h>
#include <Visual/LED.h>

class Matrix {
public:
    static void toggle_led(uint8_t x, uint8_t y)
    {
        uint8_t index = (y-1) * 6 + x - 1;
        uint8_t segment = index / 12;
        uint8_t led = index % 12;

        switch(segment)
        {
            case 0:
                // LED::set_channel(LED1202_DEV1_7BIT_ADDR, pow(2, led), true);
                break;
            case 1:
                // LED::set_channel(LED1202_DEV2_7BIT_ADDR, pow(2, led), true);
                break;
            case 2:
                // LED::set_channel(LED1202_DEV3_7BIT_ADDR, pow(2, led), true);
                break;
            case 3:
                // LED::set_channel(LED1202_DEV4_7BIT_ADDR, pow(2, led), true);
                break;
        }
    }
};