#include <Arduino.h>
#include <Wire.h>

#define LED1202_DEV1_7BIT_ADDR  (0x58)
#define LED1202_DEV2_7BIT_ADDR  (0x59)
#define LED1202_DEV3_7BIT_ADDR  (0x5A)
#define LED1202_DEV4_7BIT_ADDR  (0x5B)
#define LED1202_GLOBAL_7BIT_ADDR  (0x5C)
#define LED1202_DEVICE_ENABLE      ((uint8_t)0x01)
#define LED1202_LED_CH_ENABLE      ((uint8_t)0x02)

void writeReg(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);  
    for(size_t i = 0; i < len; ++i) Wire.write(data[i]);
    Wire.endTransmission();
}

uint16_t readReg(uint8_t addr, uint8_t reg, int len)
{ 
    Wire.beginTransmission(addr);    // Get the slave's attention, tell it we're sending a command byte
    Wire.write(reg);                               //  The command byte, sets pointer to register with address of 0x32
    Wire.endTransmission(); 
    Wire.requestFrom(addr, len);          // Tell slave we need to read 1byte from the current register
    byte MSB = Wire.read();
    byte LSB = Wire.read();

    Serial.print(MSB, BIN);   
    Serial.print(",");   
    Serial.println(LSB, BIN);   
  
    return(LSB << 8) | MSB;
}

void setChannel(uint8_t addr, uint16_t Channel, bool state)
{
    volatile int32_t ret;
    uint16_t readRegVar;
    uint16_t chRegVal;
    
    readRegVar = readReg(addr, LED1202_LED_CH_ENABLE, 2);
    Serial.println(readRegVar);
    
    if(state)
    {
        chRegVal = readRegVar | Channel;
        // chRegVal = 0xFFFF;
        writeReg(addr, LED1202_LED_CH_ENABLE, (uint8_t *)&chRegVal, 2);
    }
    else
    {
        // chRegVal = 0x0000;
        chRegVal = readRegVar & (~Channel);  
        writeReg(addr, LED1202_LED_CH_ENABLE, (uint8_t *)&chRegVal, 2);
    }
}
 
void setup()
{
    uint8_t data[] = { 0x01 };

    Wire.begin();
    Serial.begin(115200);
    Serial.println("Init");
    writeReg(LED1202_DEV1_7BIT_ADDR, LED1202_DEVICE_ENABLE, (uint8_t *)data, 1);
    delay(500);
    setChannel(LED1202_DEV1_7BIT_ADDR, 4095, false);
    delay(500);
    
    // setChannel(LED1202_DEV2_7BIT_ADDR, 4095, false);
    // setChannel(LED1202_DEV3_7BIT_ADDR, 4095, false);
    // setChannel(LED1202_DEV4_7BIT_ADDR, 4095, false);

        // setChannel(LED1202_DEV1_7BIT_ADDR, 5, true);
    
    for (uint8_t channel = 0;channel<=11;channel++)
    {
        setChannel(LED1202_DEV1_7BIT_ADDR, pow(2, channel), true);
        delay(200);
    }
    for (uint8_t channel = 11;channel>=0;channel--)
    {
        setChannel(LED1202_DEV1_7BIT_ADDR, pow(2, channel), false);
        delay(200);
    }
}
 
void loop()
{
}