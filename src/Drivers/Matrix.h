#pragma once

// Includes
#include <Arduino.h>
#include <Wire.h>

/* -------------------------------------------------------------------------- */
/*                             LED Driver Adresses                            */
/* -------------------------------------------------------------------------- */

// LED Driver Devices
#define LED1202_DEV1_ADDR (0x58)
#define LED1202_DEV2_ADDR (0x59)
#define LED1202_DEV3_ADDR (0x5A)
#define LED1202_DEV4_ADDR (0x5B)
#define LED1202_GLOBAL_ADDR (0x5C)

// LED Driver Registers
#define LED1202_DEVICE_ENABLE ((uint8_t)0x01)
#define LED1202_LED_CH_ENABLE ((uint8_t)0x02)
#define LED1202_CLK_CONFIG ((uint8_t)0xE0)
#define LED1202_CS0_LED_CURRENT ((uint8_t)0x09)
#define LED1202_PATTERN0_CS0_PWM ((uint8_t)0x1E)

/* -------------------------------------------------------------------------- */
/*                            Low Level LED Driver                            */
/* -------------------------------------------------------------------------- */

class Matrix
{
public:
    // Initialize LED Driver
    static void begin()
    {
        uint8_t init = 0x01;
        write_reg(LED1202_GLOBAL_ADDR, LED1202_DEVICE_ENABLE, &init, 1);
        toggle_subpixel(LED1202_GLOBAL_ADDR, (uint16_t)0x0FFFU, false);
    }

    // Control analog and digital dimming
    static void set_pixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b)
    {
        // Calculate LED position in row
        uint8_t led_index = (3 - x) * 3;

        // Get LED driver address
        uint8_t addresses[] = {LED1202_DEV1_ADDR, LED1202_DEV2_ADDR, LED1202_DEV3_ADDR, LED1202_DEV4_ADDR};
        uint8_t address = addresses[y];

        // Calculate brightness coefficient
        float brightness_c = brightness / 100.0;

        // Set subpixel color and power
        set_subpixel(address, led_index, r * brightness_c, g * brightness_c, b * brightness_c);
    }

    static void set_brightness(int8_t new_brightness)
    {
        // Calculate brighness change
        if(new_brightness > 100) new_brightness = 100;
        if(new_brightness < 0) new_brightness = 0;
        float brightness_change = (float)new_brightness / (float)brightness;

        if(brightness_change != 1)
        {
            // Cycle through drivers
            for(int driver = 0; driver < 4; driver++)
            {
                // Cycle through subpixels
                for(int index = 0; index < 12; index++)
                {
                    // Get LED driver address
                    uint8_t addresses[] = {LED1202_DEV1_ADDR, LED1202_DEV2_ADDR, LED1202_DEV3_ADDR, LED1202_DEV4_ADDR};
                    uint8_t address = addresses[driver];

                    // Read pixels states
                    uint8_t subpixel_register = (uint8_t)(LED1202_PATTERN0_CS0_PWM + index * 2);
                    uint16_t level_read = read_reg(address, subpixel_register);

                    // Write pixel with updated brightness
                    uint16_t new_level = level_read * brightness_change;

                    // Serial.println(new_level);
                    write_reg(address, subpixel_register, (uint8_t *)&new_level, 2); 
                }

                // Update brightness state
                brightness = new_brightness;
            }
        }
    }

    static uint8_t get_brightness()
    {
        return brightness;
    }

    // Enable/disable LED channel
    static void toggle_subpixel(uint8_t address, uint16_t channel, bool enable)
    {
        // Read current status
        uint16_t readReg, chRegVal;
        readReg = read_reg(address, LED1202_LED_CH_ENABLE);

        // Write LED enable register
        if (enable)
        {
            chRegVal = readReg | channel;
            write_reg(address, LED1202_LED_CH_ENABLE, (uint8_t *)&chRegVal, 2);
        }
        else
        {
            chRegVal = readReg & (~channel);
            write_reg(address, LED1202_LED_CH_ENABLE, (uint8_t *)&chRegVal, 2);
        }
    }

private:
    // Control LED power and PWM dimming
    static void set_subpixel(uint8_t address, uint8_t index, uint16_t red, uint16_t green, uint16_t blue)
    {
        // Enable correct LED channels
        toggle_subpixel(address, pow(2, index), red > 0);        // Red channel
        toggle_subpixel(address, pow(2, index + 1), green > 0);  // Green channel
        toggle_subpixel(address, pow(2, index + 2), blue > 0);   // Blue channel

        // Calculate 12 bit pwm levels
        uint16_t r_level = ((uint8_t *)&red)[1] | ((uint8_t *)&red)[0] << 8;
        uint16_t g_level = ((uint8_t *)&green)[1] | ((uint8_t *)&green)[0] << 4;
        uint16_t b_level = ((uint8_t *)&blue)[1] | ((uint8_t *)&blue)[0] << 4;

        // Set color with PWM
        write_reg(address, (uint8_t)(LED1202_PATTERN0_CS0_PWM + index * 2), (uint8_t *)&red, 2);
        write_reg(address, (uint8_t)(LED1202_PATTERN0_CS0_PWM + (index + 1) * 2), (uint8_t *)&green, 2);
        write_reg(address, (uint8_t)(LED1202_PATTERN0_CS0_PWM + (index + 2) * 2), (uint8_t *)&blue, 2);
    }

    // Writes register to I2C
    static void write_reg(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
    {
        // Start transmission
        Wire.beginTransmission(addr);
        Wire.write(reg);

        // Write data
        for (size_t i = 0; i < len; ++i)
            Wire.write(data[i]);

        Wire.endTransmission();
    }

    // Reads register from I2C
    static uint16_t read_reg(uint8_t addr, uint8_t reg)
    {
        // Request data from register
        Wire.beginTransmission(addr);
        Wire.write(reg);
        Wire.endTransmission();

        // Read data from register
        Wire.requestFrom(addr, 2);
        byte MSB = Wire.read();
        byte LSB = Wire.read();
        return (LSB << 8) | MSB;
    }

    // Brightness variable
    static uint8_t brightness;
};

// Initialize brightness value
uint8_t Matrix::brightness = 100;