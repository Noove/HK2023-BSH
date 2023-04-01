// Includes
#include <Visual/LED.h>
#include <Visual/Matrix.h>
#include <LSM6DSOSensor.h>
 
LSM6DSOSensor AccGyr(&Wire);

void setup()
{
    Serial.begin(115200);
    Serial.println("Init");

    // Init LED Driver
    Wire.begin();
    LED::begin();

    AccGyr.begin();
    AccGyr.Enable_X();  
    AccGyr.Enable_G();

    for (uint8_t index = 0; index < 4; index++)
    {
        Matrix::set_pixel(2, index, 0, 100, 100);
    }
}
 
void loop()
{
    int32_t accelerometer[3];
    int32_t gyroscope[3];
    AccGyr.Get_X_Axes(accelerometer);  
    AccGyr.Get_G_Axes(gyroscope);

    Serial.print(accelerometer[0]);
    Serial.print(",");
    Serial.print(gyroscope[1]);
    Serial.print(",");
    Serial.println(gyroscope[2]);
    delay(100);
}