#pragma once

// Includes
#include <Arduino.h>
#include <Drivers/LED.h>

class Matrix {
public:
    static void set_pixel(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue)
    {
        uint8_t index = y * 4 + 3 - x;

        uint8_t reverseIndex = 

        Serial.print("x: ");
        Serial.print(x);
        Serial.print(" | y: ");
        Serial.print(y);
        Serial.print(" | index: ");
        Serial.println(index);

        set_index(index, red, green, blue);
    }

private:
    // Sets a RGB color on a index
    static void set_index(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
    {
        // Calculate color index
        uint8_t color_index = index * 3;

        Serial.print("index: ");
        Serial.print(index);
        Serial.print(" | rindex: ");
        Serial.print(color_index);
        Serial.print(" | gindex: ");
        Serial.print(color_index + 1);
        Serial.print(" | bindex: ");
        Serial.println(color_index + 2);
        
        // Dimm color channels
        // LED::dimming(color_index, 20, red);
        // LED::dimming(color_index + 1, 20, green);
        // LED::dimming(color_index + 2, 20, blue);
    }
};