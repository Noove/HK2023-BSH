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

    for (uint8_t index = 0; index < 4; index++)
    {
        Matrix::set_pixel(2, index, 0, 100, 100);
    }
}
 
void loop()
{
}