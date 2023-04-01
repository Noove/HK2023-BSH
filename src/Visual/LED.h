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

/* -------------------------------------------------------------------------- */
/*                            Low Level LED Driver                            */
/* -------------------------------------------------------------------------- */

class LED {
public:
    // Configures which LED channel to use
    static void set_channel(uint16_t index, bool state)
    {
        // Get LED driver address and channel number
        uint16_t addresses[] = { LED1202_DEV1_ADDR, LED1202_DEV2_ADDR, LED1202_DEV3_ADDR, LED1202_DEV4_ADDR};
        uint16_t address = addresses[index / 12];
        uint16_t channel = pow(2, index % 12);

        // Read current status
        uint16_t readReg, chRegVal;
        readReg = read_reg(address, LED1202_LED_CH_ENABLE, 2);
        
        // Change registers according to request
        if(state)
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

    // Initialize LED Driver
    static void begin()
    {
        uint8_t init_data = 0x01;
        LED::write_reg(LED1202_GLOBAL_ADDR, LED1202_DEVICE_ENABLE, &init_data, 1);
        LED::write_reg(LED1202_GLOBAL_ADDR, LED1202_LED_CH_ENABLE, 0x0000, 2);
    }

private:
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