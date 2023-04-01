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

    for (uint8_t i = 0; i < 255; i++)
    {
        for (uint8_t y = 0; y < 4; y++)
        {
            for (uint8_t x = 0; x < 4; x++)
            {
                LED::set_pixel(x, y, i, 255 - i, 0);
            }
        }
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