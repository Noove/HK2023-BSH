#pragma once

// Includes
#include <Arduino.h>
#include <Drivers/LED.h>

class Matrix {
public:
    static void set_pixel(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue)
    {
        uint8_t index = y * 4 + 3 - x;
        set_index(index, red, green, blue);
    }

private:
    // Sets a RGB color on a index
    static void set_index(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
    {
        // Calculate color index
        uint8_t color_index = index * 3;
        
        // Dimm color channels
        LED::dimming(color_index, 255, red);
        LED::dimming(color_index + 1, 255, green);
        LED::dimming(color_index + 2, 255, blue);
    }
};