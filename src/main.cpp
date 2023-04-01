#include <Arduino.h>
#include <Wire.h>

#define LED1202_GLOBAL_7BIT_ADDR  (0x5C)
#define LED1202_DEVICE_ENABLE      ((uint8_t)0x01)

void writeReg(uint8_t add, uint8_t reg, uint8_t data)
{
    Wire.beginTransmission(add);
    Wire.write(reg);                          
    Wire.write(data);                        
    Wire.endTransmission();
} 
 
void setup()
{
    Wire.begin();
    Serial.begin(115200);
    writeReg(LED1202_GLOBAL_7BIT_ADDR, LED1202_DEVICE_ENABLE, 0x01);
}
 
void loop()
{
}