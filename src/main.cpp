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
    LED::set_color(5, 10, 0, 0);
    
    for (uint8_t index = 0;index<=4095;index++)
    {
        // LED::dimming(0, 255, index);
        delay(20);
    }
}
 
void loop()
{
}