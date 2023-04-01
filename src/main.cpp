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

    for (uint8_t index = 0; index < 16; index++)
    {
        LED::set_color(index, 255, 0, 0);
        delay(100);
        LED::set_color(15 - index, 255, 255, 0);
    }
}
 
void loop()
{
}