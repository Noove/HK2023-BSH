#include <Arduino.h>
#include <Visual/LED.h>
 
void setup()
{
    Serial.begin(115200);
    Serial.println("Init");

    // Init LED Driver
    Wire.begin();
    LED::begin();
    
    for (uint8_t channel = 0;channel<=11;channel++)
    {
        LED::set_channel(LED1202_DEV1_7BIT_ADDR, pow(2, channel), true);
        delay(200);
    }
    for (uint8_t channel = 11;channel>=0;channel--)
    {
        LED::set_channel(LED1202_DEV1_7BIT_ADDR, pow(2, channel), false);
        delay(200);
    }
}
 
void loop()
{
}