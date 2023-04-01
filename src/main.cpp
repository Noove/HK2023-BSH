// Includes
#include <Drivers/LED.h>
#include <Drivers/Matrix.h> 
#include <Drivers/Sensor.h> 

void setup()
{
    Serial.begin(115200);
    Serial.println("Init");

    // Devices
    Wire.begin();
    LED::begin();
    Sensor::begin();

    // LED::dimming(0, 10, 255);
    // LED::dimming(1, 10, 192);
    // LED::dimming(2, 10, 203);

// Matrix::set_pixel(2, 2, 255, 192, 203);

    for (uint8_t x = 0; x < 4; x++)
    {
        for (uint8_t y = 0; y < 4; y++) Matrix::set_pixel(x, y, 255, 192, 203);
    }
}
 
void loop()
{
    // int8_t level[2];
    // Sensor::get_level(level);
    // Serial.print("Pitch: ");
    // Serial.print(level[0]);
    // Serial.print(" | Roll: ");
    // Serial.println(level[1]);

    delay(200);
}