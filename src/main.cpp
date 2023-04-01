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

    for (uint8_t index = 0; index < 4; index++)
    {
        Matrix::set_pixel(2, index, 0, 100, 100);
    }
}
 
void loop()
{
    int8_t level[2];
    Sensor::get_level(level);
    Serial.print("Pitch: ");
    Serial.print(level[0]);
    Serial.print(" | Roll: ");
    Serial.println(level[1]);

    delay(200);
}