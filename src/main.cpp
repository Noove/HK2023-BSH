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

    // Matrix::toggle_led(3, 4);
    
    for (uint8_t index = 0;index<=48;index++)
    {
        LED::set_channel(index, true);
        delay(200);
    }
}
 
void loop()
{
}