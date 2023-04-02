// Includes
#include <Drivers/Matrix.h>
#include <Drivers/Sensor.h>
#include <Drivers/Animation.h>

void setup()
{
    Serial.begin(115200);

    // Devices
    Wire.begin();
    Matrix::begin();
    Sensor::begin();
    Matrix::set_brightness(20);
}

void loop()
{    
    Animation::runAnimation();
}