#pragma once

// Includes
#include <Arduino.h>
#include <Wire.h>

/* -------------------------------------------------------------------------- */
/*                             LED Driver Adresses                            */
/* -------------------------------------------------------------------------- */

// LED Driver Devices
#define LED1202_DEV1_ADDR  (0x58)
#define LED1202_DEV2_ADDR  (0x59)
#define LED1202_DEV3_ADDR  (0x5A)
#define LED1202_DEV4_ADDR  (0x5B)
#define LED1202_GLOBAL_ADDR  (0x5C)

// LED Driver Registers
#define LED1202_DEVICE_ENABLE      ((uint8_t)0x01)
#define LED1202_LED_CH_ENABLE      ((uint8_t)0x02)
#define LED1202_CS0_LED_CURRENT  ((uint8_t)0x09)
#define LED1202_PATTERN0_CS0_PWM  ((uint8_t)0x1E)

// HW config
#define MAX_CH_CURRENT 20

/* -------------------------------------------------------------------------- */
/*                            Low Level LED Driver                            */
/* -------------------------------------------------------------------------- */

class LED {
public:
    // Configures which LED channel to use
    static void set_color(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
    {
        // Calculate color index
        uint8_t color_index = index * 3;
        
        // Dimm color channels
        dimming(color_index, 255, red);
        dimming(color_index + 1, 255, green);
        dimming(color_index + 2, 255, blue);
    }

    // Initialize LED Driver
    static void begin()
    {
        uint8_t init_data = 0x01;
        LED::write_reg(LED1202_GLOBAL_ADDR, LED1202_DEVICE_ENABLE, &init_data, 1);
        LED::write_reg(LED1202_GLOBAL_ADDR, LED1202_LED_CH_ENABLE, 0x0000, 2);
    }

    // Control analog and digital dimming
    static void dimming(uint8_t index, uint8_t analog, uint16_t digital)
    {
        // Get LED driver address and channel
        uint8_t addresses[] = { LED1202_DEV1_ADDR, LED1202_DEV2_ADDR, LED1202_DEV3_ADDR, LED1202_DEV4_ADDR};
        uint8_t address = addresses[index / 12];
        uint16_t channel = pow(2, index % 12);

        // Disable channel if brightness is 0
        if(digital > 0)
        {
            toggle_channel(address, channel, true);

            // Analog Dimming
            write_reg(address, (LED1202_CS0_LED_CURRENT + channel), &analog, 1); 

            // Digital dimming
            uint16_t channel_offset = (((uint16_t)2)*channel) + (((uint16_t)24)*0);
            if(channel == 1) channel_offset = 0;
            write_reg(address,(uint8_t)(LED1202_PATTERN0_CS0_PWM + channel_offset), (uint8_t *)&digital, 2); 
        }
        else
        {
            toggle_channel(address, channel, false);
        }
    }

private:
    // Enable/disable LED channel
    static void toggle_channel(uint8_t address, uint16_t channel, bool enable)
    {
        // Read current status
        uint16_t readReg, chRegVal;
        readReg = read_reg(address, LED1202_LED_CH_ENABLE, 2);

        // Write LED enable register
        if(enable)
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

    // Writes register to I2C
    static void write_reg(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
    {
        // Start transmission
        Wire.beginTransmission(addr);
        Wire.write(reg);  

        // Write data
        for(size_t i = 0; i < len; ++i) Wire.write(data[i]);
        
        Wire.endTransmission();
    }

    // Reads register from I2C
    static uint16_t read_reg(uint8_t addr, uint8_t reg, int len)
    { 
        // Request data from register
        Wire.beginTransmission(addr);    
        Wire.write(reg);                               
        Wire.endTransmission(); 

        // Read data
        Wire.requestFrom(addr, len);        
        byte MSB = Wire.read();
        byte LSB = Wire.read();
        return(LSB << 8) | MSB;
    }
};