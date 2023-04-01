// Includes
#include <Visual/LED.h>
#include <Visual/Matrix.h>
 
void setup()
{
    Serial.begin(115200);
    Serial.println("Init");

    // Init LED Driver
    Wire.begin();
    LED::begin();

    for (uint8_t index = 0; index < 48;index++)
    {
        LED::dimming(index, 255, 255);
        delay(200);
        LED::dimming(index, 255, 0);
    }
}
 
void loop()
{
}