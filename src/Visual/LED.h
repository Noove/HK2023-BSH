// Includes
#include <Arduino.h>
#include <Wire.h>

/* -------------------------------------------------------------------------- */
/*                             LED Driver Adresses                            */
/* -------------------------------------------------------------------------- */

// LED Driver Devices
#define LED1202_DEV1_7BIT_ADDR  (0x58)
#define LED1202_DEV2_7BIT_ADDR  (0x59)
#define LED1202_DEV3_7BIT_ADDR  (0x5A)
#define LED1202_DEV4_7BIT_ADDR  (0x5B)
#define LED1202_GLOBAL_7BIT_ADDR  (0x5C)

// LED Driver Registers
#define LED1202_DEVICE_ENABLE      ((uint8_t)0x01)
#define LED1202_LED_CH_ENABLE      ((uint8_t)0x02)

/* -------------------------------------------------------------------------- */
/*                            Low Level LED Driver                            */
/* -------------------------------------------------------------------------- */

class LED {
public:
    // Configures which LED channel to use
    static void set_channel(uint8_t addr, uint16_t Channel, bool state)
    {
        volatile int32_t ret;
        uint16_t readRegVar;
        uint16_t chRegVal;
        
        readRegVar = read_reg(addr, LED1202_LED_CH_ENABLE, 2);
        Serial.println(readRegVar);
        
        if(state)
        {
            chRegVal = readRegVar | Channel;
            write_reg(addr, LED1202_LED_CH_ENABLE, (uint8_t *)&chRegVal, 2);
        }
        else
        {
            chRegVal = readRegVar & (~Channel);  
            write_reg(addr, LED1202_LED_CH_ENABLE, (uint8_t *)&chRegVal, 2);
        }
    }

    // Initialize LED Driver
    static void begin()
    {
        uint8_t init_data[] = { 0x01 };
        LED::write_reg(LED1202_DEV1_7BIT_ADDR, LED1202_DEVICE_ENABLE, (uint8_t *)init_data, 1);
        LED::set_channel(LED1202_DEV1_7BIT_ADDR, 4095, false);
    }

private:
    // Writes register to I2C
    static void write_reg(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
    {
        Wire.beginTransmission(addr);
        Wire.write(reg);  
        for(size_t i = 0; i < len; ++i) Wire.write(data[i]);
        Wire.endTransmission();
    }

    // Reads register from I2C
    static uint16_t read_reg(uint8_t addr, uint8_t reg, int len)
    { 
        Wire.beginTransmission(addr);    // Get the slave's attention, tell it we're sending a command byte
        Wire.write(reg);                               //  The command byte, sets pointer to register with address of 0x32
        Wire.endTransmission(); 
        Wire.requestFrom(addr, len);          // Tell slave we need to read 1byte from the current register
        byte MSB = Wire.read();
        byte LSB = Wire.read();
        return(LSB << 8) | MSB;
    }
};